First and foremost, you need a standard LAMP stack.  nginx can be substituted fro Apache if you are more comfortable with that, and I suppose that you could do this on a Windows server as well, but it would just be wrong to do so and you're on your own.  To make it look pretty I used WordPress as a base, so that is the first thing that you should get going.  There are plenty of guides on how to install and configure it, so I won't reproduce those steps here.

Take a random JPG and make eight copies of it naming them:

daily.jpg
dailyp.jpg
week.jpg
weekp.jpg
month.jpg
monthp.jpg
year.jpg
yearp.jpg

Upload these to your WordPress site.  These are the files that will be overwritten by your scripts to generate the graphs dynamically.

Make a copy of the JPG that you are using for the front page of the theme that you are using.  If you don't start with a fresh copy every time that makefrontpage.py runs, then you'll end up with black stripes instead of data on the front page.

The Python libraries that you'll need are Pandas, PIL (Python Image Library) and matplotlib.  You can either install them with pip or your package manager, but keep in mind that when installing with pip your computer needs to compile stuff.  If you're using something rinky-dink like a Raspberry Pi, it will take ages for the compilation to take place.  Pandas is used for the SQL stuff, PIL generates the JPG on the front page, and matplotlib is used to generate the graphs.

To set up the database run the DatabaseCreation SQL script.

Make a directory within /var/www/html called weather.  Copy the following process.php, makefrontpage.py, and plot_daily.py to it, making sure to populate the SQL authentication with your own, and setting the file paths properly.

Copy plot_daily.py to:

plot_week.py
plot_month.py
plot_year.py

Edit each of those scripts replacing "INTERVAL 1 DAY" with WEEK, MONTH, and YEAR respectively.  Also remember to change the file name to week.jpg, weekp.jpg, etc.

Run "crontab -e" and add the following to it to automatically run the python scripts:

*/10 * * * * python /var/www/html/weather/makefrontpage.py
*/20 * * * * python /var/www/html/weather/plot_daily.py
0 * * * * python /var/www/html/weather/plot_week.py
10 0 * * * python /var/www/html/weather/plot_month.py
30 0 * * * python /var/www/html/weather/plot_year.py

