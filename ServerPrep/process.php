<?php

$temperature=$_POST['temperature'];
$humidity=$_POST['humidity'];
$pressure=$_POST['pressure'];
$heatindex=$_POST['heatindex'];
$con=mysqli_connect('localhost','username','password');
$sql=("INSERT INTO weather_data(temperature,humidity,pressure,heatindex)
        VALUES('$temperature','$humidity','$pressure','$heatindex')");

if (!mysqli_query($con,$sql))

  {

  die('Error: ' . mysqli_error());

  }

echo "1 record added";
mysqli_close($con);
echo 'Done!';
?>

