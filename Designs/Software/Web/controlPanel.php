<?php
  session_start();
  if(!$_SESSION['isLoggedIn']) {
     header("Location: /login.php");
     die();
  }
  class Point {
    public $x = 0;
    public $y = 0;
    function __construct($x_,$y_) {
      $this->x = $x_;
      $this->y = $y_;
    }
    function toString() {
      return "{x:new Date('$this->x'),y:$this->y}";
    }
  }
  include "dbinfo.php";
  $h2o_level = [];

  $sql = 'SELECT h2o_level, h2o_stored, time FROM TestTable ORDER BY time DESC LIMIT 180';
  $result = mysqli_query($conn,$sql);
  if(!$result) {
    die('Could not get data: ' . mysqli_error());
  }
  // Why are the timestamps 7 hours off?
  $sevenHours = 25200;
  $i = 0;
  while($row=mysqli_fetch_array($result,MYSQLI_ASSOC)) {
    // $h2o_level[$i] = new Point(strtotime($row['time'])-$now+$sevenHours,$row['h2o_level']);
    $h2o_level[$i] = new Point($row['time'],$row['h2o_level']);
    //echo $h2o_level[$i]->x." ";
    $i++;
  }

  function getData() {
    global $h2o_level;
    // isFirst flag so I can include the comma
    $isFirst = TRUE;
    foreach($h2o_level as $point) {
      if(!$isFirst) {
        echo ",";
      }
      $isFirst = FALSE;
      echo $point->toString();
    }
    
  }


?>

<!DOCTYPE html>
<html lang="en">
<head>
  <title>Hydroponic Automation | Control Panel</title>
  <meta charset="utf-8">

  <!-- Bootstrap 4 -->
  <!-- Responsive Layout -->
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>

  <!-- Charts -->
  <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.bundle.min.js"></script>

</head>
<body>

<!-- Navbar -->
<?php include 'nav.php'; ?>

<div class="container" style="margin-top:30px;margin-bottom:30px">
    <div class="row justify-content-center align-items-center">
      <div id="login-column" class="col-md-6">
        <canvas id="myChart" width="400" height="400"></canvas>
        <script type="text/javascript">
          var ctx = $("#myChart");
          var myChart = new Chart(ctx, {
            type: 'scatter',
            data: {
              datasets: [{
                label: 'Scatter Dataset',
                showLine: true,
                data: [<?php getData() ?>]
              }]
            },
            options: {
              scales: {
                xAxes: [{
                  type: 'time',
                  time: {
                    unit: 'hour'
                  }
                }]
              },
              legend: {
                display: false
              }
            }
          });
        </script>
      </div>
    </div>
</div>


<!-- Footer to replaced by jQuery and footer.html -->
<div id="footer-placeholder"></div>
<script>$(function(){$("#footer-placeholder").load("footer.html");});</script>



<!-- https://bootsnipp.com/snippets/featured/login-form -->
</body>
</html>
