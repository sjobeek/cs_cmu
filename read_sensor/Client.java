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
import java.io.*;
import java.net.*;

class Client
{
	public static void main(String args[]) throws Exception
	{
		String 	junk;				// Temporary string 
		String 	START = "start\n";	// String that signals the DataGen server to begin sending data
		int 	Hours;				// Data sample time stamp hours
		int 	Minutes;			// Data sample time stamp minutes
		int 	Seconds;			// Data sample time stamp seconds
		float	Humidity;			// Relative Humidity
		float	Temperature;		// Temperature in Degrees Fahrenheit 	
		float	Pressure;			// Pressure in Kilo Pascals (kPa)
		int		portID;				// Server socket port

		// Here we check to see if there is a port number specified on the command line.
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
		
		} // server port
		
		// This is used to get input from the user
		BufferedReader UserInput = new BufferedReader( new InputStreamReader(System.in));
		
		// This is the socket used to connect to the server
		Socket clientSocket = new Socket("localhost", 6789);
		
		// This is the stream used to send data to the server
		DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());

		// This is the stream used to read data from the server for reading data
		DataInputStream inFromServer = new DataInputStream(clientSocket.getInputStream());
  	  	
  		// Here we ask the user to press enter to begin data collection from the server...
  		
		System.out.println( "\n\nPress enter to begin data collection...\n" );  				
		junk = UserInput.readLine();
		
 		// Send the start string to the server to begin collecting data...
 		
  		outToServer.writeBytes(START);		
  		
  		// Data loop... I only collect 30 samples...
  		
  		for (int i=0; i<30; i++)
  		{
	  		// Here we read the data from the socket...
	  		
 			Hours = inFromServer.readInt();
	  		Minutes = inFromServer.readInt();
  			Seconds = inFromServer.readInt();
  			Humidity = inFromServer.readFloat();
  			Temperature = inFromServer.readFloat();  		
  			Pressure = inFromServer.readFloat();  		

  			// Here we display the data...
  			
  			System.out.println( "Time: " + Hours + ":" + Minutes + ":" + Seconds + "\t- " + " Hum: " + Humidity + " Temp: " + Temperature + "F"  + " Pres: " + Pressure + "kPa" ) ; 
  			
		} // for
		
		// Closing the socket is a signal to the DataGen server that you don't want any more data.
		
		clientSocket.close();
  		
 	} // main 
 	
} // Client Class