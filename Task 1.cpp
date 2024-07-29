#pragma warning(disable : 26812)
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <json/json.h> 

using namespace std;

class WeatherVariable
{
public:
    WeatherVariable();
    ~WeatherVariable();
    void updateVariable(double, double, double, string, string, int);
    void displayVariable();

private:
    string timeZone;
    string currentTime;
    double precpitation;
    double temperature;
    double windSpeed;
    int humidity;
};

WeatherVariable::WeatherVariable()
{
    temperature = 0.00;
    windSpeed = 0.00;
    humidity = 0;
    timeZone = "";
    currentTime = "";
    precpitation = 0.00;

}

WeatherVariable::~WeatherVariable()
{
    // destructor
}

void WeatherVariable::updateVariable(double temp, double windSp, double precp, string Tz, string Ct, int humm) {
    temperature = temp;
    windSpeed = windSp;
    humidity = humm;
    precpitation = precp;
    timeZone = Tz;
    currentTime = Ct;
}

void WeatherVariable::displayVariable() {
    cout << "\nTemp: " << temperature;
    cout << "\nHumidity: " << humidity;
    cout << "\nWind Speed: " << windSpeed;
    cout << "\npreceptation: " << precpitation;
    cout << "\ntime zone: " << timeZone;
    cout << "\ncurrent time: " << currentTime;

}

class Location
{
public:
    Location();
    ~Location() {
        //destructor
    }
    void addLocation(double, double, string, double, double, double, string, string, int);
    void dispLocation();
private:
    string name;
    double latitude;
    double longitude;
    WeatherVariable variable;
};
Location::Location() {
    name = "";
    latitude = 0.00;
    longitude = 0.00;
}
void Location::addLocation(double lat, double lon, string nameLoc, double temp, double windSp, double precp, string Tz, string Ct, int humm) {
    name = nameLoc;
    latitude = lat;
    longitude = lon;
    variable.updateVariable(temp, windSp, precp, Tz, Ct, humm);
}
void Location::dispLocation() {
    cout << "\n\n" << name;
    cout << "\n....................\n";
    cout << "\nlatitude: " << latitude;
    cout << "\nlongitude: " << longitude;
    cout << "\nweather variables: ";
    variable.displayVariable();
}

class WeatherForcastingSystem
{
public:
    WeatherForcastingSystem() {
        // constructor
    }
    ~WeatherForcastingSystem() {
        // destructor
    }
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    auto fetchData() -> Json::Value;
private:

};

size_t WeatherForcastingSystem::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

auto WeatherForcastingSystem::fetchData() -> Json::Value {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.open-meteo.com/v1/forecast?latitude=33.5406,33.5872&longitude=73.1426,73.0399&current=temperature_2m,relative_humidity_2m,precipitation,wind_speed_10m&timezone=auto&start_date=2024-07-11&end_date=2024-07-17");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WeatherForcastingSystem::WriteCallback); // Use the static member function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    // Parse the JSON response using jsoncpp
    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonData;
    std::string errs;

    std::istringstream stream(readBuffer);
    if (!Json::parseFromStream(readerBuilder, stream, &jsonData, &errs)) {
        std::cerr << "Failed to parse JSON: " << errs << std::endl;
        return Json::Value(); // return empty Json::Value on failure
    }



    return jsonData;
}

int main() {
    WeatherForcastingSystem obj;
    auto JsonData = obj.fetchData();

    Location loc[2];
    int i = 0;
    double lat, longi, precp, temp, WS;
    string TZ, CT, name;
    int hum;
    for (const auto& location : JsonData) {

        lat = location["latitude"].asDouble();
        longi = location["longitude"].asDouble();
        TZ = location["timezone"].asString();
        CT = location["current"]["time"].asString();
        temp = location["current"]["temperature_2m"].asDouble();
        hum = location["current"]["relative_humidity_2m"].asInt();
        precp = location["current"]["precipitation"].asDouble();
        WS = location["current"]["wind_speed_10m"].asDouble();
        std::cout << "----------------------------------------\n";
        if (i == 0) {
            name = "Islamabad";
        }
        else if (i == 1) {
            name = "Rawalpindi";
        }

        loc[i].addLocation(lat, longi, name, temp, WS, precp, TZ, CT, hum);
        i++;
    }

    for (int i = 0; i < 2; i++) {
        cout << "\n\n";
        loc[i].dispLocation();
        cout << "\n";
    }
    return 0;
}
