CREATE data;
USE data;
CREATE TABLE weather_data (
  id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  created TIMESTAMP DEFAULT NOW(),
  temperature DECIMAL(6,2),
  humidity DECIMAL(6,2),
  pressure DECIMAL(6,2),
  heatindex DECIMAL(6,2)
);
