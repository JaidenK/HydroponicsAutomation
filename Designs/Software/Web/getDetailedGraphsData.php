<?php 
  // session_start();
  // if(!$_SESSION['isLoggedIn']) {
  //    die("You must be logged in to view graph data.");
  // }

// A simple (x,y) point with a function to JSONify it.
class Point {
  public $x = 0;
  public $y = 0;
  function __construct($x_,$y_) {
    $this->x = $x_;
    $this->y = $y_;
  }
  function toJSONString() {
    return '{"x":"'.$this->x.'","y":"'.$this->y.'"}';
  }
}

// Create a connection
include "dbinfo.php";
// The array of points
$allData = [];

// Product ID unused 
// $ProductID = mysqli_real_escape_string($conn, $_POST["ProductID"]);
// valueKey unused
// $valueKey = mysqli_real_escape_string($conn, $_POST["valueKey"]);
// How far in the past to select data
$interval = (int) ($_POST["interval"]);

$sql = "SELECT h2o_level, ph_level, ph_target, ec_level, ec_target, flow_measured, flow_target, time FROM TestTable WHERE time > date_sub(now(), interval '$interval' minute);";
$result = mysqli_query($conn,$sql) or die('Could not get data: ' . mysqli_error($conn));

$i = 0;
while($row=mysqli_fetch_array($result,MYSQLI_ASSOC)) {
  // $h2o_level[$i] = new Point(strtotime($row['time'])-$now+$sevenHours,$row['h2o_level']);
  $allData["h2o_level"][$i] = new Point($row['time'],$row['h2o_level']);
  $allData["h2o_stored"][$i] = new Point($row['time'],$row['h2o_stored']);
  $allData["ph_level"][$i] = new Point($row['time'],$row['ph_level']);
  $allData["ph_target"][$i] = new Point($row['time'],$row['ph_target']);
  $allData["ec_level"][$i] = new Point($row['time'],$row['ec_level']);
  $allData["ec_target"][$i] = new Point($row['time'],$row['ec_target']);
  $allData["flow_measured"][$i] = new Point($row['time'],$row['flow_measured']);
  $allData["flow_target"][$i] = new Point($row['time'],$row['flow_target']);
  $i++;
}

function getData($valueKey) {
  global $allData;
  // isFirst flag so I can include the comma
  $isFirst = TRUE;
  foreach($allData[$valueKey] as $point) {
    if(!$isFirst) {
      echo ",";
    }
    $isFirst = FALSE;
    echo $point->toJSONString();
  }
}
echo '{';
  echo '"h2o_level":[';
    getData('h2o_level');
  echo '],';
  echo '"h2o_stored":[';
    getData('h2o_stored');
  echo '],';
  echo '"ph_level":[';
    getData('ph_level');
  echo '],';
  echo '"ph_target":[';
    getData('ph_target');
  echo '],';
  echo '"ec_level":[';
    getData('ec_level');
  echo '],';
  echo '"ec_target":[';
    getData('ec_target');
  echo '],';
  echo '"flow_measured":[';
    getData('flow_measured');
  echo '],';
  echo '"flow_target":[';
    getData('flow_target');
  echo ']';
echo '}';
/*
{
  "points":[
    {"x":"asdf","y":"asdf"},
    {"x":"asdf","y":"asdf"}
  ]
}
*/

?>
