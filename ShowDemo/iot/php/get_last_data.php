<?php
	header("Content-type:text/html;charset=utf-8");
  require("./security/db_conf.php");

  $clientID = $_GET['id'];
  if($clientID == null)
      die('Error search!');

	$con = mysql_connect($mysql_server_name,$mysql_username,$mysql_password);
	if (!$con)
  	{
  		die('Could not connect: ' . mysql_error());
  	}

  mysql_query("set names 'utf8'");
	mysql_select_db($mysql_database, $con); 

  $result = mysql_query("SELECT * FROM `".$clientID."` ORDER BY ctime DESC LIMIT 1;");
  $raw_data = "";
  $json_data = ""; 
  class TimeContent 
  {
    public $time;
    public $vol;
    public $tmp;
    public $hum;
    public $ctime;
  }

  $row = mysql_fetch_array($result);
  $time_content = new TimeContent();
  $time_content->time = $row['时间'];
  $time_content->vol = $row['电压'];
  $time_content->tmp = $row['温度'];
  $time_content->hum = $row['湿度'];
  $time_content->ctime = $row['ctime'];
  $raw_data = $time_content;
  
  $json_data = json_encode($raw_data);

  echo $json_data;
  mysql_close($con);
?>
