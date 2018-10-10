<?php
function receiveStreamFile($receiveFile)
{
    $streamData = isset($GLOBALS['HTTP_RAW_POST_DATA'])? $GLOBALS['HTTP_RAW_POST_DATA'] : '';
    if(empty($streamData))
    {
        $streamData = file_get_contents('php://input');
    }
    if($streamData!='')
    {
        $ret = file_put_contents($receiveFile, $streamData, true);
    }
    else
    {
        $ret = false;
    }

    return $ret;
}

$receiveFile = '../upload/' . $_GET['fileName'];
$ret = receiveStreamFile($receiveFile);
echo json_encode(array('success'=>(bool)$ret));


?>

