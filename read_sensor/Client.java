
/******************************************************************************************************************
 * File:Client.java
 * Course: 17630
 * Project: Secondary Storage, I/O, and Management Assignment
 * Copyright: Copyright (c) 2011 Carnegie Mellon University
 * Versions:
 *	1.0 November 2011 - Original write (Anthony J. Lattanze).
 *
 * Description:
 *
 * This class serves as a template for creating a client task to read data from the DataGen server. This class will
 * connect to the DataGen server and prompt the user to press enter to begin data acquisition. Once the user presses
 * enter, this program will then go into data acquisition mode reading buffers of data from the DataGen server
 * process. Note that by default, this client program will use port number 6789 unless another port is specified on
 * the command line. Of course the client program and DataGen must use the same port number. Another assumption that
 * is made is that the client is on the same processor as the DataGen server process.
 *
 * Parameters: Port Number
 *
 * Internal Methods: None
 *
 ******************************************************************************************************************/
import com.sun.xml.internal.bind.v2.TODO;

import java.io.*;
import java.net.*;
import java.nio.file.*;
import java.util.*;

class MeasurementReading{
	String description;
	float measurement;

	public MeasurementReading (String desc, float measure){
		this.description = desc;
		this.measurement = measure;
	}
}

class Measurements {
	ArrayList<MeasurementReading> al = new ArrayList<MeasurementReading>();
	String readingTime;
	public Measurements(String timestamp, float measure1, float measure2, float measure3){
		this.readingTime = timestamp;
		this.al.add(new MeasurementReading("Humidity",measure1));
		this.al.add(new MeasurementReading("Temperature",measure2));
		this.al.add(new MeasurementReading("Pressure",measure3));
	}

	public Measurements(String timestamp){
		this.readingTime = timestamp;
	}

	public void addMeasurementReading(String desc, float measurement){
		this.al.add(new MeasurementReading(desc, measurement));
	}


	public String toString(){
		String ret = this.readingTime;
		if (al.size() == 3){
			ret = ret + ",Hum:" + al.get(0).measurement + ",Temp:" +
					al.get(1).measurement + "F"  + ",Pres:" + al.get(2).measurement + "kPa" ;
		}
		return ret;
	}
}

class Client
{
    //  Structure to organize all of the Measurement objects
	private static ArrayList<Measurements> listOfMeasures = new ArrayList<Measurements>();

	public static void main(String args[]) throws Exception
	{
		int	portID;		// Server socket port

		// Here we check to see if there is a port number specified on the command line and set server port accordingly.
		if ( args.length > 0 )
		{
			try {
				// use port number provided on the command line
				System.out.println( "Using port:: " + args[0] );
				portID = new Integer( args[0] );
			} // try
			catch (NumberFormatException IOError)
			{
				// means port number provided on the command line is invalid
				// we set the port number to 6789 and let the user know
				portID = 6789;
				System.out.println( "\nSpecified port number on command line " + args[0] + " is invalid as port number." );
				System.out.println( "\nDefault port number:: " + portID + " will be used." );
			} // catch
		} else {
			// no port number specified, so we set the port number to 6789
			portID = 6789;
			System.out.println( "Using port:: " + portID );
		} // setting server port

		//  Prompting user if they would like to refresh the local data and listen to the available DataGenerator
		Scanner UserInput = new Scanner(System.in);

        //  Find all files that have measurement data stored in them
		ArrayList<String> inputDataFiles = retrievePossibleDatasets();
		System.out.println("Number of tracked datasets is " + inputDataFiles.size());
        //  Load the data stored in local disk to application memory for processing
		loadAllData(inputDataFiles);

		while (true) {
			//  Get the menu for what services are provided
			System.out.println("\n\nMain Menu- Select an option by pressing its key followed by enter\n" +
					"'r'- Gathers the latest data \n" +
					"'b'- Prepares the data to be stored in a buffer and made available to the user\n" +
					"'f'- Initiates a find of the first occurence with option to then find the next occurrence\n" +
					"'s'- Presents a summary of each data file that is currently tracked \n" +
					"'q'- Quits the application \n\n");

			char c = UserInput.next().charAt(0);

            //  Option for gathering 5 minutes of data from the Data Generator
			if (c == 'r') {
				System.out.println("The data will be gathered if the source is available on the port " + portID);
				String tempReturnElem = refreshDataSource();
				System.out.println(tempReturnElem + " was successfully stored.");

            //  Option for searching on a measurement type and value.
			} else if (c == 'f') {
                //  Initial value to distinguish the different measurement types
				int searchType = Integer.MAX_VALUE;
				System.out.println("What measurement would you like to search on?");
				while (searchType == Integer.MAX_VALUE) {
                    //  This is the default options for measurements of humidity, temperature, pressure
					if (listOfMeasures.get(0).al.size() == 3) {
						System.out.println("You're options will be 0: Humidity, 1: Temperature, 2: Pressure");
						char fc = UserInput.next().charAt(0);
						if (fc == '0') {
							searchType = 0;
						} else if (fc == '1') {
							searchType = 1;
						} else if (fc == '2') {
							searchType = 2;
						} else {
							System.out.println("The type you entered was " + fc + " please use one of the following" +
                                    " characters {0, 1, 2}");
						}
					//  If it is any option other than the default options, don't bother to do any mapping of numbers
                    //  to the different options and instead rely on the user having knowledge of the changes that were
                    //  made to the Data Generation server.  We enforce that the number entered is less than the overall
                    // size but nothing else.
					} else {
						System.out.println("Please choose an index below the number of measurements we have, " +
								"which is " + listOfMeasures.get(0).al.size() + ", please try again.");
						String fc = UserInput.next();
						if (Integer.parseInt(fc) < listOfMeasures.get(0).al.size()) {
							searchType = Integer.parseInt(fc);
						}
					}
				}

				//  What value would you like to search on?
				System.out.println("What value would you like to search on?");
				//  Get the user's value after they press enter
                String value = UserInput.next();
                //  Convert the User's value to a float and read through the structure with for the search type with the
                //  similar value
				String retTimestampFirst = findFirstOccurrence(searchType, Float.parseFloat(value));
                //  Convert the User's value to a float and read through the structure with for the search type with the
                //  similar value.  This time we start at the index+1 we were able to find in findFirstOccurrence
				String retTimestampNext = findNextOccurrence(Integer.parseInt(retTimestampFirst.split("__")[1]),
                        searchType, Float.parseFloat(value));
				System.out.println("The value: " + Float.parseFloat(value) + " for searchType: " + searchType + " was started at and then completed at "
						+ retTimestampFirst.split("__")[0] + "_" + retTimestampNext);
			//  Allows gaining a quick view of all the data that has been processed and stored by the application
			} else if (c == 's') {
				for (String s : inputDataFiles) {
					System.out.println("Filename: " + s + " Summary Information: " + summaryRetrieval(s));
				}
			//  API should allow a user to request data in chunks that meet the buffer standards
			} else if (c == 'b'){
                // TODO: Need to implement delivery via binary buffer

            //  A user needs to be able to quit the application and break from the while true loop
			} else if (c == 'q') {
				return;
            //  Handling the null case in the event the User does not have the best intentions.
			} else {
				System.out.println("You entered the character " + c + " which is not recognized by the system as {r, " +
						"f, s, or q}.  Please select from this list and press enter.");
			}
		}

	} // main



	private static void loadAllData(ArrayList<String> inputDataFiles){
		for (String s: inputDataFiles){
			listOfMeasures.addAll(loadData(s));
		}

		System.out.println("Number of tracked measurements is " + listOfMeasures.size());
	}

	private static List<Measurements> loadData(String sourceFile ){
		List<Measurements> measures = new ArrayList<Measurements>();
		try
		{
			BufferedReader reader = new BufferedReader(new FileReader(sourceFile));
			String currentLine;
			while ((currentLine = reader.readLine()) != null)
			{
				String[] splitLine = currentLine.split(",");
				Measurements tempMeasurement;
				if (splitLine.length == 4){
					tempMeasurement = new Measurements(splitLine[0], Float.parseFloat(splitLine[1].split(":")[1]),
							Float.parseFloat(splitLine[2].split(":")[1]), Float.parseFloat(splitLine[3].split(":")[1].replace("kPa","")));
					System.out.println( tempMeasurement.toString());
				} else {
					tempMeasurement = new Measurements(splitLine[0]);
					for (int i=1; i<splitLine.length;++i){
						tempMeasurement.addMeasurementReading("Generic Reading", Float.parseFloat(splitLine[i].split(":")[1]));
					}
				}

				measures.add(tempMeasurement);
			}
			reader.close();
			return measures;
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		return measures;
	}

	private static ArrayList<String> retrievePossibleDatasets(){
		ArrayList<String> alDatasets = new ArrayList<String>();
		try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get("."), "Sensor*.txt")) {
			for (Path dataSet : dirStream)
			{
				alDatasets.add(dataSet.toString());
			}

		}catch (Exception e){
			e.printStackTrace();
		}

		return alDatasets;
	}

	private static String refreshDataSource() throws Exception{
		String 	junk;				// Temporary string
		String 	START = "start\n";	// String that signals the DataGen server to begin sending data
		int 	Hours;				// Data sample time stamp hours
		int 	Minutes;			// Data sample time stamp minutes
		int 	Seconds;			// Data sample time stamp seconds
		float	Humidity;			// Relative Humidity
		float	Temperature;		// Temperature in Degrees Fahrenheit
		float	Pressure;			// Pressure in Kilo Pascals (kPa)
		// This is used to get input from the user
		BufferedReader UserInput = new BufferedReader( new InputStreamReader(System.in));

		// This is the socket used to connect to the server
		Socket clientSocket = new Socket("localhost", 6789);

		// This is the stream used to send data to the server
		DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());

		// This is the stream used to read data from the server for reading data
		DataInputStream inFromServer = new DataInputStream(clientSocket.getInputStream());
		//BufferedReader d = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

		// Here we ask the user to press enter to begin data collection from the server...

		System.out.println( "\n\nPress enter to begin data collection...\n" );
		junk = UserInput.readLine();

		// Send the start string to the server to begin collecting data...

		outToServer.writeBytes(START);
		//String minTimeStamp = "";
		int minHours= Integer.MAX_VALUE, minMinutes = Integer.MAX_VALUE, minSeconds= Integer.MAX_VALUE;
		//String maxTimeStamp = "";
		int maxHours= Integer.MIN_VALUE, maxMinutes = Integer.MIN_VALUE, maxSeconds= Integer.MIN_VALUE;

		// Data loop... I only collect 30 samples...
		BufferedWriter bw = new BufferedWriter(
				new OutputStreamWriter( new FileOutputStream("tempFileName1234124.txt"), "utf-8"));
		for (int i=0; i<10; i++)
		{
			// Here we read the data from the socket...
			//System.out.println(d.readLine());

			Hours = inFromServer.readInt();
			Minutes = inFromServer.readInt();
			Seconds = inFromServer.readInt();
			//String timeStamp = new String(Hours + ":" + Minutes + ":" +Seconds);
			if (Hours <= minHours){
				minHours = Hours;
				if (Minutes < minMinutes){
					minMinutes = Minutes;
					minSeconds = Seconds;
				} else if (Minutes == minMinutes){
					if (Seconds < minSeconds){
						minSeconds = Seconds;
					}
				}
			}

			if (Hours >= maxHours){
				maxHours = Hours;
				if (Minutes > maxMinutes){
					maxMinutes = Minutes;
					maxSeconds = Seconds;
				} else if (Minutes == maxMinutes) {
					if (Seconds > maxSeconds){
						maxSeconds = Seconds;
					}
				}
			}

			Humidity = inFromServer.readFloat();
			Temperature = inFromServer.readFloat();
			Pressure = inFromServer.readFloat();
			String outString = Hours + ":" + Minutes + ":" + Seconds + ",Hum:" + Humidity + ",Temp:" + Temperature + "F"  + ",Pres:" + Pressure + "kPa" ;

			bw.write(outString);
			bw.newLine();

			// Here we display the data...
			System.out.println( "Time: " + Hours + ":" + Minutes + ":" + Seconds + "\t- " + " Hum: " + Humidity + " Temp: " + Temperature + "F"  + " Pres: " + Pressure + "kPa" ) ;

		} // for
		String minTimeStamp = new String(minHours + "_" + minMinutes + "_" + minSeconds);
		String maxTimeStamp = new String(maxHours + "_" + maxMinutes + "_" + maxSeconds);

		bw.close();

		String newFilename = null;
		try {
			Path source = new File("tempFileName1234124.txt").toPath();
			newFilename = new String("Sensor__" + minTimeStamp + "__" + maxTimeStamp+ ".txt");
			Files.move(source, source.resolveSibling(newFilename));
		} catch(Exception e){
			// if any error occurs
			e.printStackTrace();
		}

		System.out.println("Minimum timestamp is " + minTimeStamp);
		System.out.println("Maximum timestamp is " + maxTimeStamp);
		// Closing the socket is a signal to the DataGen server that you don't want any more data.

		clientSocket.close();
		if (newFilename != null){
			return newFilename;
		} else {
			return "Something went wrong, check the exception stack.";
		}

	}

	private static String findFirstOccurrence(int searchIndex, float targetValue){
		boolean found = false;
		String readingTime = null;
		int i = 0;
		while (!found && i < listOfMeasures.size()){
			if (!found && listOfMeasures.get(i).al.get(searchIndex).measurement == targetValue){
				found = true;
				return listOfMeasures.get(i).readingTime + "__"+ i;
			}else {
				i= i+1;
			}
		}
		return readingTime;
	}

	private static String findNextOccurrence(int startIndex, int searchIndex, float targetValue){
		String firstReadingTime = null;
		int i = startIndex +1;
		while ( i < listOfMeasures.size()){
			if (listOfMeasures.get(i).al.get(searchIndex).measurement == targetValue){
				return listOfMeasures.get(i).readingTime;
			}else {
				i= i+1;
			}
		}
		return firstReadingTime;
	}

	//      Summary data function that tells users what measurements are in the file, the
	//		measurement units, the measurement type, how much data has been collected (in
	//		bytes), and the time span of the data.
	private static String summaryRetrieval(String sourceFile){
		String returnString = null;
		File dataChecking = new File(sourceFile);
		returnString = "Size of the data collected is " + dataChecking.length() + "\n";
		String[] parsedFilename = sourceFile.split("__");
		returnString += "Time span of the data collected is " + parsedFilename[1] +
				" and " + parsedFilename[2].replace(".txt","") + "\n";

		try
		{
			BufferedReader reader = new BufferedReader(new FileReader(sourceFile));
			String currentLine;
			if ((currentLine = reader.readLine()) != null)
			{
				String[] splitLine = currentLine.split(",");
				if (splitLine.length == 4)
				{
					returnString += "The measurements we have taken are Humidity (measured in a percentage) " +
							"Pressure (measured in kila-Pascal), and Temperature (measured in Fahrenheidht \n";
				}else {
					returnString += "The measurements we have taken are Humidity (measured in a percentage) " +
							"Pressure (measured in kila-Pascal), and Temperature (measured in Fahrenheidht";
					for (int i = 4; i<splitLine.length; ++i){
						returnString += splitLine[i];
					}
				}
			}
			reader.close();
		} catch (Exception e){

		}
		return returnString;
	}

} // Client Class




//	Your job is to collect data for 5 minutes and store it in on disk in a format of your own design or
//		selection. You can select/design any kind of storage structure/strategy you like that supports
//		the following user needs and adheres to the following constraints and assumptions:
//
//		1. Assume that users are scientists who want to access the data from applications that they
//		will write. The users need to be able to search and access specific data based on various
//		search criteria. All data storage details should be completely hidden from the users. Users
//		expect to be able to use your APIs to search and access data.
//
//		2. You will need to provide the following APIs:
//		    • Summary data function that tells users what measurements are in the file, the
//		measurement units, the measurement type, how much data has been collected (in
//		bytes), and the time span of the data.
//		    • Search by finding the first-occurrence function of a particular data value and when it
//		occurs as well as a next-occurrence function that finds the next occurrence of the
//		data value as well as when it occurs in the data. The function should return the time
//		index of the frame where the data begins.


//		    • Read data function that reads and fills buffers of data. Users will provide the start
//		and stop time as well as the measurements of interest. The API will return buffers of
//		data to the user. Note that if there is more data than can be reasonably packed into
//		a single buffer, the API should signal the programmer in some way that there is
//		more data to read.

//      Buffer size of 4096 as the least common denominator for disk block size as the cutoff

//
//		3. Because the users will use Java to write their applications, you must use Java to build your
//		APIs. Assume that users will not install anything else on their systems to use your APIs
//		other than the JRE and Java SDK that is already installed on their system.
//
//		4. Your user APIs should be configurable and support reading data streams with different
//		measurements other than those provided by DataGen. You should assume that time in the
//		current format will always be present.
