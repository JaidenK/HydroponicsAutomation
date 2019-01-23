<?php

include "dbinfo.php";

// This all should be changed to a $_POST to increase security, reliability, and allow longer string.
if($_GET['ProductID'] != "password") {
   die("Invalid product id.");
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
   die("Bad request.");
}

// TODO this needs to be cleaned up and refactored. Too much reppetitiotns 
$h2o_level = (double)$_GET["h2o_level"];
$h2o_stored = (double) $_GET["h2o_stored"];
$ph_level = (double) $_GET["ph_level"];
$ph_up_stored = (double) $_GET["ph_up_stored"];
$ph_down_stored = (double) $_GET["ph_down_stored"];
$ec_level = (double) $_GET["ec_level"];
$ec_stored = (double) $_GET["ec_stored"];
$temp_measured = (double) $_GET["temp_measured"];
$flow_measured = (double) $_GET["flow_measured"];
$flow_target = (double) $_GET["flow_target"];
$ph_target = (double) $_GET["ph_target"];
$ec_target = (double) $_GET["ec_target"];



$sql = "INSERT INTO `TestTable` (`h2o_level`, `h2o_stored`, `ph_level`, `ph_up_stored`, `ph_down_stored`, `ec_level`, `ec_stored`, `temp_measured`, `flow_measured`, `flow_target`, `ph_target`, `ec_target`, `time`, `table_key`) VALUES ('$h2o_level', '$h2o_stored', '$ph_level', '$ph_up_stored', '$ph_down_stored', '$ec_level', '$ec_stored', '$temp_measured', '$flow_measured', '$flow_target', '$ph_target', '$ec_target', CURRENT_TIMESTAMP, NULL);";

if ($conn->query($sql) === TRUE) {
   echo "new_record=success\n";
} else {
   echo "new_record=error\n";
   echo "Error: " . $sql . "<br>" . $conn->error;
}

?> 
