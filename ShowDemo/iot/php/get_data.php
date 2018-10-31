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

  $result = mysql_query("SELECT `时间`,`电压`,`温度`,`湿度`,DATE_FORMAT(ctime,'%H:%i') AS ctime FROM (SELECT `时间`,`电压`,`温度`,`湿度`,ctime FROM (SELECT * FROM `".$clientID."` ORDER BY ctime DESC LIMIT 10) AS result ORDER BY ctime) AS real_result;");
  $json_data = ""; 
  $array = array();
  class TimeContent 
  {
    public $time;
    public $vol;
    public $tmp;
    public $hum;
    public $ctime;
  }

  while($row = mysql_fetch_array($result))
  {
    $time_content = new TimeContent();
    $time_content->time = $row['时间'];
    $time_content->vol = $row['电压'];
    $time_content->tmp = $row['温度'];
    $time_content->hum = $row['湿度'];
    $time_content->ctime = $row['ctime'];
    $array[] = $time_content;
  }
  $json_data = json_encode($array);

  echo $json_data;
  mysql_close($con);
?>
