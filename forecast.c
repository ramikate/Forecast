#include "forecast.h"

/* Function that converts Celsius degrees to Fahrenheit */
float celsiusToFahrenheit(float celsius) {
	float fahrenheit;
	
	fahrenheit = (celsius * FAHRENHEIT_FACTOR) + FAHRENHEIT_OFFSET;
    return fahrenheit;
}

/* Function that converts Fahrenheit degrees to Celsius */
float fahrenheitToCelsius(float fahrenheit) {
	float celsius;
	
	celsius = (fahrenheit - FAHRENHEIT_OFFSET) * CELSIUS_FACTOR;	
    return celsius;
}


/* Exercise 1 */
/* Function to load ski resort data from file */
void loadSkiResortsDataFromFile(const char* filename, tTemperature scale, tSkiResortsTable *resortsTable, bool* isRead) {
    FILE* fin = NULL;
    char line[MAX_LINE];
	char buffer[MAX_LINE];
    tSkiResort newResort;
    int i;
	
	float temperatureVector [DAYS_IN_WEEK];
	float rainAccumulationVector [DAYS_IN_WEEK];
	tWeatherData weatherDataTmp;

    /* Open the input file */
    if ((fin = fopen(filename, "r")) != NULL) {
		
		/* Exercise 1.1 */
		/* Initialize resort table */
        resortsTable->nResorts = 0;
		/****************************/
		
        /* Read all the resorts */  
        while (!feof(fin) && resortsTable -> nResorts < MAX_RESORTS) {
            /* Remove any content from the line */
            line[0] = '\0';

            /* Read one line (maximum MAX_LINE chars) and store it in "line" variable */
            fgets(line, MAX_LINE - 1, fin);

            /* Ensure that the string is ended by 0 */
            line[MAX_LINE - 1] = '\0';

            if (strlen(line) > 0) {
                /* Obtain the resort name and weather data from the file line */
                sscanf(line, "%s %[^\n]s", newResort.resortName, buffer);
				for (i = 0; i < DAYS_IN_WEEK; i++) {
					sscanf(buffer, "%f %f %[^\n]s", &temperatureVector[i], &rainAccumulationVector[i], buffer);
				}
	
				/* Generate wheather data and add them to the vector */
				for (i = 0; i < DAYS_IN_WEEK; i++) {
					
					/* Exercise 1.2 */					
					/* If Fahrenheit is needed, convert the temperature */					
					if (scale == FAHRENHEIT) {
                        weatherDataTmp.temperature = celsiusToFahrenheit(temperatureVector[i]);
                    } else {
                        weatherDataTmp.temperature = temperatureVector[i];
                    }
					/************************************************************/
					weatherDataTmp.rainAccumulation = rainAccumulationVector[i];					
					newResort.weekData[i] = weatherDataTmp;
				}	
				
				/* Exercise 1.3 */
				/* Add new resort to resorts vector */
				resortsTable->resorts[resortsTable->nResorts] = newResort;
                resortsTable->nResorts++;
                /**************************************/	
            }
        }
        /* Close the file */
        fclose(fin);
        *isRead = true;
    } 
	else {
        *isRead = false;
    }
}

/* Exercise 2 */
bool isSnowyWeek(tSkiResort resort, tTemperature scale) {
	bool itWillSnow = false;
    int i;
    float temp;

    for (i = 0; i < DAYS_IN_WEEK && !itWillSnow; i++) {
        // Convert temperature to Celsius if needed
        if (scale == FAHRENHEIT) {
            temp = fahrenheitToCelsius(resort.weekData[i].temperature);
        } else {
            temp = resort.weekData[i].temperature;
        }

        // Check snow condition
        if (temp <= SNOW_TEMP_CELSIUS_THRESHOLD &&
            resort.weekData[i].rainAccumulation >= SNOW_RAIN_THRESHOLD) {
            itWillSnow = true;
        }
    }
	return itWillSnow;
}

/* Exercise 3 */
void getExtremeTempForecast(tSkiResort resort, float* minTemp, float* maxTemp) {
    int i;

    // Ini var with first day
    *minTemp = resort.weekData[0].temperature;
    *maxTemp = resort.weekData[0].temperature;

    for (i = 1; i < DAYS_IN_WEEK; i++) {
        if (resort.weekData[i].temperature < *minTemp) {
            *minTemp = resort.weekData[i].temperature;
        }
        if (resort.weekData[i].temperature > *maxTemp) {
            *maxTemp = resort.weekData[i].temperature;
        }
    }
}


/* Exercise 4 */
void getResortsWithSnowPrediction(tSkiResortsTable table, tTemperature scale, tSkiResortsTable* resultTable) {
    int i;

    resultTable->nResorts = 0;

    for (i = 0; i < table.nResorts; i++) {
        if (isSnowyWeek(table.resorts[i], scale)) {
            resultTable->resorts[resultTable->nResorts] = table.resorts[i];
            resultTable->nResorts++;
        }
    }
}
