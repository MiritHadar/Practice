Author: 		Ori Michaeli
Project:		Open Weather
Last update: 	09-01-2020


/*	To Compile	*/

1) Install curl.
2) You should download the curl lib using:
sudo apt-get install libcurl-dev 

and if this is not possible you should download using:
 sudo apt-get install libcurl4-gnutls-dev

3) Use make in command line

/*	To run	*/
for example: 
	./open_weather.out -K 99e09c7c1ee20a10c7329264895ff394 -c London -a pressure

/*	Notes		*/

1) I used libcurl library for the http get request.
2) I would have used a library for parsing the JSON if i had more time(I parsed it manually).
