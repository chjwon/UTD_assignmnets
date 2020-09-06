#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
#include <iomanip>
#include <stdint.h>
using namespace std;
#define GroundStationOutputChannel cout

const string TELEMETRY_RECIEVER_INPUT_CHANNEL = "inputDataAntenna.txt";

enum class MESSAGE_ID {	SATELLITE_INTORMATION_MESSAGE = 1, EXPERIMENT_INFORMATION_MESSAGE = 2, SEND_SUMMARY_MESSAGE = 3};
MESSAGE_ID messageID;

enum InformationType { SATELLITE_INFORMATION, EXPIRIMENT_INFORMATION,EMPTY};
const uint16_t ARRAY_DATA_STORAGE_SIZE = 5; //const uint8_t

struct SatelliteInformation {
	float_t temperature;
	float_t voltage;
};

struct ExperimentInformation {
	uint16_t radiationCount;
	uint16_t latchupEventsCount;
};

union MasterUnion {
	SatelliteInformation satelliteInformaion;
	ExperimentInformation expirimantInformation;
};

struct MasterInformation {
	InformationType infoType;
	MasterUnion masterUnion;

};


int main() {
	MasterInformation infoStoredArray[ARRAY_DATA_STORAGE_SIZE];
	uint16_t          entryPositionIndex = 0;
	MasterInformation masterInformation;

	ifstream          telemetryInputAntennaReceiverChannel;
	telemetryInputAntennaReceiverChannel.open(TELEMETRY_RECIEVER_INPUT_CHANNEL, ios::in);



	if (telemetryInputAntennaReceiverChannel.fail()) {
		cout << "File " << TELEMETRY_RECIEVER_INPUT_CHANNEL << " could not be opened !" << endl;
		cout << "Press enter key to continue....";
		cin.ignore();
		cin.get();
		exit(EXIT_FAILURE);
	}
	GroundStationOutputChannel << setprecision(1) << fixed << showpoint;

	for (uint16_t index = 0; index < ARRAY_DATA_STORAGE_SIZE; index++) {
		infoStoredArray[index].infoType = EMPTY;
	}

	uint16_t val;

	while ((telemetryInputAntennaReceiverChannel >> val)) {
		messageID = MESSAGE_ID(val);
		switch (messageID) {
		case MESSAGE_ID::SATELLITE_INTORMATION_MESSAGE:
			masterInformation.infoType = SATELLITE_INFORMATION;
			telemetryInputAntennaReceiverChannel >>
				masterInformation.masterUnion.satelliteInformaion.temperature>>
				masterInformation.masterUnion.satelliteInformaion.voltage;
			infoStoredArray[entryPositionIndex] = masterInformation;
			entryPositionIndex = (entryPositionIndex == 4) ? 0 : ++entryPositionIndex;
			break; //MESSAGE_ID::SATELLITE_INFORMATION_MESSAGE

		case MESSAGE_ID::EXPERIMENT_INFORMATION_MESSAGE:
			masterInformation.infoType = SATELLITE_INFORMATION;
			telemetryInputAntennaReceiverChannel >>
				masterInformation.masterUnion.expirimantInformation.radiationCount >>
				masterInformation.masterUnion.expirimantInformation.latchupEventsCount;
			infoStoredArray[entryPositionIndex] = masterInformation;
			entryPositionIndex = (entryPositionIndex == 4) ? 0 : ++entryPositionIndex;
			break; //MESSAGE_ID::EXPERIMENT_INFORMATION_MESSAGE

		case MESSAGE_ID::SEND_SUMMARY_MESSAGE:
			//summary information
			float_t maxTemperature = -50,   // -50 - 212
				    minTemperature = 212;
			float_t maxVoltage = 0.0,
				    minVoltage = 100.0;

			uint16_t totalRadiationCount = 0,
				     totalLatchupEventCount = 0,
				     infoSICount = 0,
				     infoEICount = 0;

			for (uint8_t index = 0; index < ARRAY_DATA_STORAGE_SIZE; index++) {
				switch (infoStoredArray[index].infoType) {

				case SATELLITE_INFORMATION:
					GroundStationOutputChannel <<
						"Temperature : " <<
						infoStoredArray[index].masterUnion.satelliteInformaion.temperature <<endl<<
						"Voltage     : " <<
						infoStoredArray[index].masterUnion.satelliteInformaion.voltage <<endl<<
						infoSICount++;
					//set min max summary information
					if (maxTemperature < infoStoredArray[index].masterUnion.satelliteInformaion.temperature) {
						maxTemperature = infoStoredArray[index].masterUnion.satelliteInformaion.temperature;
					}
					if (minTemperature > infoStoredArray[index].masterUnion.satelliteInformaion.temperature) {
						minTemperature = infoStoredArray[index].masterUnion.satelliteInformaion.temperature;
					}
					if (maxVoltage < infoStoredArray[index].masterUnion.satelliteInformaion.voltage) {
						maxVoltage = infoStoredArray[index].masterUnion.satelliteInformaion.voltage;
					}
					if (minVoltage < infoStoredArray[index].masterUnion.satelliteInformaion.voltage) {
						minVoltage = infoStoredArray[index].masterUnion.satelliteInformaion.voltage;
					}
					break; //case SATELLITE_INFORMATION

				case EXPIRIMENT_INFORMATION:
					GroundStationOutputChannel <<
						"Radiation Count     : " <<
						infoStoredArray[index].masterUnion.expirimantInformation.radiationCount << endl <<
						"Latchup Event Count : " <<
						infoStoredArray[index].masterUnion.expirimantInformation.latchupEventsCount << endl << endl;
					infoEICount++;

					totalRadiationCount += infoStoredArray[index].masterUnion.expirimantInformation.radiationCount;
					totalLatchupEventCount += infoStoredArray[index].masterUnion.expirimantInformation.latchupEventsCount;
					break;//case EXPIRIMENT_INFORMATION:

				case EMPTY:
					//do nothing for empty array items(skip)
					break;// case EMPTY

				}// switch (infoStoredArray[index].infoType)
			}//for

			GroundStationOutputChannel <<
				"Summary Information" << endl <<
				"-------------------" << endl <<
				"Number of Satellite Information Records : " << infoSICount << endl <<
				"Number of Satellite Information Records : " << infoEICount << endl <<
				"Total Radiation Count      : " << totalRadiationCount << endl <<
				"Total Latchup Event Count  : " << totalLatchupEventCount << endl <<
				"Maximum Temperature        : " << maxTemperature << endl <<
				"Minimum Temperature        : " << minTemperature << endl <<
				"Maximum Voltage            : " << maxVoltage << endl <<
				"Minimum Voltage            : " << minVoltage << endl << endl;

			//hold screen
			cout << "Press the enter key to continue...";
			cin.ignore();
			cin.get();

		}//switch(messageID)
	}//while(!(telemetryInputAntennaReceiverChannel>>val))

	return (EXIT_SUCCESS);

}