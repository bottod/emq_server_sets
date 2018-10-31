<?php
    header("Content-type:text/html;charset=utf-8");
    require("./security/db_conf.php");

    $con = mysql_connect($mysql_server_name,$mysql_username,$mysql_password);
    if (!$con)
    {
        die('Could not connect: ' . mysql_error());
    }

    mysql_query("set names 'utf8'");
    mysql_select_db($mysql_database, $con);

    $result = mysql_query("show tables;");
    $json_data = "";
    $array = array();

     while($row = mysql_fetch_array($result))
    {
        $tab = $row['Tables_in_mq_playground'];
        $array[] = ($tab);
    }
    $json_data = json_encode($array);

    echo $json_data;
    mysql_close($con);
?>