<?php 

// A simple (x,y) point with a function to JSONify it.
class Point {
  public $x = 0;
  public $y = 0;
  function __construct($x_,$y_) {
    $this->x = $x_;
    $this->y = $y_;
  }
  function toJSONString() {
    return "{'x':'$this->x','y':$this->y}";
  }
}

// Create a connection
include "dbinfo.php";
// The array of points
$allData = [];

// Product ID unused 
$ProductID = mysqli_real_escape_string($conn, $_POST["ProductID"]);
// The column to select
$valueKey = mysqli_real_escape_string($conn, $_POST["valueKey"]);
// How far in the past to select data
$interval = (int) ($_POST["interval"]);


$sql = "SELECT '$valueKey', 'time' FROM TestTable WHERE time > date_sub(now(), interval $interval minute);";
$result = mysqli_query($conn,$sql) or die('Could not get data: ' . mysqli_error());

$i = 0;
while($row=mysqli_fetch_array($result,MYSQLI_ASSOC)) {
  // $h2o_level[$i] = new Point(strtotime($row['time'])-$now+$sevenHours,$row['h2o_level']);
  $allData[$valueKey][$i] = new Point($row['time'],$row[$valueKey]);
  $i++;
}

echo "{'points':[";
// isFirst flag so I can include the comma
$isFirst = TRUE;
foreach($allData[$valueKey] as $point) {
  if(!$isFirst) {
    echo ",";
  }
  $isFirst = FALSE;
  echo $point->toString();
}
echo "]}";

/*
{
  "points":[
    {"x":"asdf","y":"asdf"},
    {"x":"asdf","y":"asdf"}
  ]
}
*/

?>
