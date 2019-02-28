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
      return "{x:moment('$this->x','YYYY-MM-DD HH:mm:ss'),y:$this->y}";
    }
  }
  include "dbinfo.php";
  $allData = [];

  $sql = 'SELECT h2o_level, ph_level, ph_target, ec_level, ec_target, flow_measured, flow_target, time FROM TestTable WHERE time > date_sub(now(), interval 30 minute);';
  $result = mysqli_query($conn,$sql);
  if(!$result) {
    die('Could not get data: ' . mysqli_error());
  }
  // Why are the timestamps 7 hours off?
  $sevenHours = 25200;
  $i = 0;
  while($row=mysqli_fetch_array($result,MYSQLI_ASSOC)) {
    // $h2o_level[$i] = new Point(strtotime($row['time'])-$now+$sevenHours,$row['h2o_level']);
    $allData["h2o_level"][$i] = new Point($row['time'],$row['h2o_level']);
    //$allData["h2o_stored"][$i] = new Point($row['time'],$row['h2o_stored']);
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
  <script src="http://momentjs.com/downloads/moment.js"></script>

  <script type="text/javascript">
    function rebuildCharts() {
      var ctx = $("#myChart1");
      var myChart = new Chart(ctx, {
        type: 'scatter',
        data: {
          datasets: [{
            label: 'Level',
            showLine: true,
            data: [<?php getData("h2o_level") ?>],
            backgroundColor: "rgba(85,85,255,0.1)",
            borderColor: "rgba(85,85,255,0.8)"
          }]
          // },{
          //   label: 'Stored',
          //   showLine: true,
          //   data: [<?php getData("h2o_stored") ?>],
          //   backgroundColor: "rgba(0,0,0,0)",
          //   borderColor: "rgba(30,30,100,0.8)"
          // }]
        },
        options: {
          title: {
            display: true,
            text: "Water"
          },
          scales: {
            xAxes: [{
              type: 'time',
            }],
            yAxes: [{
              display: true,
              ticks: {
                suggestedMin: 0
              }
            }]
          },
          legend: {
            display: true
          }
        }
      });
      var phCtx = $("#phChart");
      var phChart = new Chart(phCtx, {
        type: 'scatter',
        data: {
          datasets: [{
            label: 'Level',
            showLine: true,
            data: [<?php getData("ph_level") ?>],
            backgroundColor: "rgba(85,255,85,0.1)",
            borderColor: "rgba(85,255,85,0.8)"
          },{
            label: 'Target',
            showLine: true,
            data: [<?php getData("ph_target") ?>],
            backgroundColor: "rgba(0,0,0,0)",
            borderColor: "rgba(30,100,30,0.8)"
          }]
        },
        options: {
          title: {
            display: true,
            text: "pH"
          },
          scales: {
            xAxes: [{
              type: 'time',
            }],
            yAxes: [{
              display: true,
              ticks: {
                suggestedMin: 0
              }
            }]
          },
          legend: {
            display: true
          }
        }
      });
      var ecCtx = $("#ecChart");
      var ecChart = new Chart(ecCtx, {
        type: 'scatter',
        data: {
          datasets: [{
            label: 'Level',
            showLine: true,
            data: [<?php getData("ec_level") ?>],
            backgroundColor: "rgba(136, 102, 68, 0.1)",
            borderColor: "rgba(136, 102, 68, 0.8)"
          },{
            label: 'Target',
            showLine: true,
            data: [<?php getData("ec_target") ?>],
            backgroundColor: "rgba(0,0,0,0)",
            borderColor: "rgba(60, 40, 20,0.8)"
          }]
        },
        options: {
          title: {
            display: true,
            text: "EC"
          },
          scales: {
            xAxes: [{
              type: 'time',
            }],
            yAxes: [{
              display: true,
              ticks: {
                suggestedMin: 0
              }
            }]
          },
          legend: {
            display: true
          }
        }
      });

      var flowCtx = $("#flowChart");
      var flowChart = new Chart(flowCtx, {
        type: 'scatter',
        data: {
          datasets: [{
            label: 'Measured',
            showLine: true,
            data: [<?php getData("flow_measured") ?>],
            backgroundColor: "rgba(0, 128, 128, 0.1)",
            borderColor: "rgba(0, 128, 128, 0.8)"
          },{
            label: 'Target',
            showLine: true,
            data: [<?php getData("flow_target") ?>],
            backgroundColor: "rgba(0,0,0,0)",
            borderColor: "rgba(0, 100, 100,0.8)"
          }]
        },
        options: {
          title: {
            display: true,
            text: "Flow"
          },
          scales: {
            xAxes: [{
              type: 'time',
            }],
            yAxes: [{
              display: true,
              ticks: {
                suggestedMin: 0
              }
            }]
          },
          legend: {
            display: true
          }
        }
      });
    }
    $(document).ready(function(){
      rebuildCharts();
    })
  </script>
</head>
<body>

<!-- Navbar -->
<?php include 'nav.php'; ?>

<div class="container" style="margin-top:30px;margin-bottom:30px">
    <div class="row justify-content-center align-items-center">
      <div class="col col-lg-6 col-sm-12">
        <canvas id="myChart1"></canvas>
      </div>
      <div class="col col-lg-6 col-sm-12">
        <canvas id="phChart"></canvas>
      </div>
      <div class="col col-lg-6 col-sm-12">
        <canvas id="ecChart"></canvas>
      </div>
      <div class="col col-lg-6 col-sm-12">
        <canvas id="flowChart"></canvas>
      </div>
    </div>
</div>


<!-- Footer to replaced by jQuery and footer.html -->
<div id="footer-placeholder"></div>
<script>$(function(){$("#footer-placeholder").load("footer.html");});</script>



<!-- https://bootsnipp.com/snippets/featured/login-form -->
</body>
</html>
