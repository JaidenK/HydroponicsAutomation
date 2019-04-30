<?php

include "dbinfo.php";
include "notificationSystem.php";

// This all should be changed to a $_POST to increase security, reliability, and allow longer string.
if($_GET['ProductID'] != "ABCD1234EFGH5678") {
   die("new_record=Invalid product id: ".$_GET['ProductID']."\n");
}

$keys = array(
   "h2o_level",
   "h2o_stored",
   "ph_level",
   "ph_up_stored",
   "ph_down_stored",
   "ec_level",
   "ec_stored",
   "temp_measured",
   "flow_measured",
   "flow_target",
   "ph_target",
   "ec_target"
);

$isBadRequest = false; 

$valuesString = "";
foreach($keys as $key) {
   if(!array_key_exists($key, $_GET)) {
      echo $key." missing.\n";
      $isBadRequest = true;
   }
}

if($isBadRequest) {
   die("new_record=error\n");
}

// TODO this needs to be cleaned up and refactored. Too much reppetitiotns 
$h2o_level =      (double)$_GET["h2o_level"];
$h2o_stored =     (double) $_GET["h2o_stored"];
$ph_level =       (double) $_GET["ph_level"];
$ph_up_stored =   (double) $_GET["ph_up_stored"];
$ph_down_stored = (double) $_GET["ph_down_stored"];
$ec_level =       (double) $_GET["ec_level"];
$ec_stored =      (double) $_GET["ec_stored"];
$temp_measured =  (double) $_GET["temp_measured"];
$flow_measured =  (double) $_GET["flow_measured"];
$flow_target =    (double) $_GET["flow_target"];
$ph_target =      (double) $_GET["ph_target"];
$ec_target =      (double) $_GET["ec_target"];

$ProductID = mysqli_real_escape_string($conn, $_GET["ProductID"]);

if($_GET["notify"]) {
   sendNotification($ProductID,mysqli_real_escape_string($conn, $_GET["notify"]));
}


$sql = "INSERT INTO `TestTable` (`h2o_level`, `h2o_stored`, `ph_level`, `ph_up_stored`, `ph_down_stored`, `ec_level`, `ec_stored`, `temp_measured`, `flow_measured`, `flow_target`, `ph_target`, `ec_target`, `time`, `table_key`) VALUES ('$h2o_level', '$h2o_stored', '$ph_level', '$ph_up_stored', '$ph_down_stored', '$ec_level', '$ec_stored', '$temp_measured', '$flow_measured', '$flow_target', '$ph_target', '$ec_target', CURRENT_TIMESTAMP, NULL);";

if ($conn->query($sql) === TRUE) {
   echo "new_record=success\n";
} else {
   echo "new_record=error\n";
   echo "Error: " . $sql . "<br>" . $conn->error;
}

$sql = "SELECT * FROM `MachineConfig` WHERE `ProductID` = '$ProductID'";
$result = mysqli_query($conn,$sql) or die(mysql_error());
while($row=mysqli_fetch_array($result,MYSQLI_ASSOC)) {
  echo "water_target ".$row['water']."\n";
  echo "ph_target ".$row['ph']."\n";
  echo "ec_target ".$row['ec']."\n";
  echo "flow_target ".$row['flow']."\n";
  echo "temp_target ".$row['temp']."\n";
}
$sql = "UPDATE `MachineConfig` SET water=0, ph=0, ec=0, flow=0, temp=0 WHERE `ProductID` = '$ProductID'";
$result = mysqli_query($conn,$sql) or die(mysql_error());
?> 
