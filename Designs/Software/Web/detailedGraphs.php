<?php
  session_start();
  if(!$_SESSION['isLoggedIn']) {
     header("Location: /login.php");
     die();
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
    $(document).ready(function(){
      var updateInterval;
      var historyInterval = 30;

      var h2oCtx = $("#h2oChart");
      var h2oChart;
      var phCtx = $("#phChart");
      var phChart;
      var ecCtx = $("#ecChart");
      var ecChart;
      var flowCtx = $("#flowChart");
      var flowChart;

      var h2o_level_data = [];
      var h2o_stored_data = [];
      var ph_level_data = [];
      var ph_target_data = [];
      var ec_level_data = [];
      var ec_target_data = [];
      var flow_measured_data = [];
      var flow_target_data = [];

      // func is a callback since ajax is non blocking.
      function ajaxGetData(func) {
        $.post(
          'getDetailedGraphsData.php',
          $("#chartForm").serialize(),
          function( data, textStatus, jQxhr ){
            try {
              // JSON parsing might not succeed
              var obj = JSON.parse(data);
              // We use h2o_level length yet do all the entries because
              // they should all be the same length
              for (var i = 0; i < obj.h2o_level.length; i++) {
                h2o_level_data[i] = {
                  x: moment(obj.h2o_level[i].x,'YYYY-MM-DD HH:mm:ss'),
                  y: obj.h2o_level[i].y
                };
                h2o_stored_data[i] = {
                  x: moment(obj.h2o_stored[i].x,'YYYY-MM-DD HH:mm:ss'),
                  y: obj.h2o_stored[i].y
                };
                ph_level_data[i] = {
                  x: moment(obj.ph_level[i].x,'YYYY-MM-DD HH:mm:ss'),
                  y: obj.ph_level[i].y
                };
                ph_target_data[i] = {
                  x: moment(obj.ph_target[i].x,'YYYY-MM-DD HH:mm:ss'),
                  y: obj.ph_target[i].y
                };
                ec_level_data[i] = {
                  x: moment(obj.ec_level[i].x,'YYYY-MM-DD HH:mm:ss'),
                  y: obj.ec_level[i].y
                };
                ec_target_data[i] = {
                  x: moment(obj.ec_target[i].x,'YYYY-MM-DD HH:mm:ss'),
                  y: obj.ec_target[i].y
                };
                flow_measured_data[i] = {
                  x: moment(obj.flow_measured[i].x,'YYYY-MM-DD HH:mm:ss'),
                  y: obj.flow_measured[i].y
                };
                flow_target_data[i] = {
                  x: moment(obj.flow_target[i].x,'YYYY-MM-DD HH:mm:ss'),
                  y: obj.flow_target[i].y
                };
              }
              func();
            } catch(err) {
              alert("Chart update error: "+err+"\n\n"+data);
            }
          },
          'text'
        ).fail(function(xhr, status, error) {
          alert( "Could not update charts. " + error );
        });
      }
      function buildCharts() {
        ajaxGetData(function() {
          h2oChart = new Chart(h2oCtx, {
            type: 'scatter',
            data: {
              datasets: [{
                label: 'Level',
                showLine: true,
                data: h2o_level_data,
                backgroundColor: "rgba(85,85,255,0.1)",
                borderColor: "rgba(85,85,255,0.8)"
              }]
              // },{
              //   label: 'Stored',
              //   showLine: true,
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
          phChart = new Chart(phCtx, {
            type: 'scatter',
            data: {
              datasets: [{
                label: 'Level',
                showLine: true,
                data: ph_level_data,
                backgroundColor: "rgba(85,255,85,0.1)",
                borderColor: "rgba(85,255,85,0.8)"
              },{
                label: 'Target',
                showLine: true,
                data: ph_target_data,
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
          ecChart = new Chart(ecCtx, {
            type: 'scatter',
            data: {
              datasets: [{
                label: 'Level',
                showLine: true,
                data: ec_level_data,
                backgroundColor: "rgba(136, 102, 68, 0.1)",
                borderColor: "rgba(136, 102, 68, 0.8)"
              },{
                label: 'Target',
                showLine: true,
                data: ec_target_data,
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
          flowChart = new Chart(flowCtx, {
            type: 'scatter',
            data: {
              datasets: [{
                label: 'Measured',
                showLine: true,
                data: flow_measured_data,
                backgroundColor: "rgba(0, 128, 128, 0.1)",
                borderColor: "rgba(0, 128, 128, 0.8)"
              },{
                label: 'Target',
                showLine: true,
                data: flow_target_data,
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
        });      
      }
      function updateCharts() {
        ajaxGetData(function() {
          // TODO the chart doesn't delete points if you shorted the 
          // timeframe
          h2oChart.update();
          phChart.update();
          ecChart.update();
          flowChart.update();
        });
      }
      buildCharts();
      updateInterval = setInterval(updateCharts,5000);

      $("#settingsToggle").click(function(){
        $("#settingsQuote").toggle();
      });
      $("#settingsQuote").hide();
      $("#chartForm").change(function(){
        clearInterval(updateInterval);
        updateInterval = setInterval(updateCharts,$("#frequency").val()*1000);
        console.log("New update interval: "+$("#frequency").val());
        var newHistoryInterval = $("#interval").val()
        if(newHistoryInterval != historyInterval) {
          historyInterval = newHistoryInterval;

          h2oChart.destroy();
          phChart.destroy();
          ecChart.destroy();
          flowChart.destroy();

          h2o_level_data = [];
          h2o_stored_data = [];
          ph_level_data = [];
          ph_target_data = [];
          ec_level_data = [];
          ec_target_data = [];
          flow_measured_data = [];
          flow_target_data = [];

          buildCharts();
        }
      }).submit(function(e){
        e.preventDefault();
      });
    })
  </script>
</head>
<body>

<!-- Navbar -->
<?php include 'nav.php'; ?>

<div class="container" style="margin-top:30px;margin-bottom:30px">
  <div class="row">
    <div class="col">
      Settings <button type="submit" id="settingsToggle" class="btn btn-primary btn-sm">Toggle</button>
      <blockquote class="blockquote" id="settingsQuote">
        <form id="chartForm">
            <div class="form-group row">
              <label for="frequency" class="col-form-label">Update Frequency:</label>
              <div class="col col-sm-6 col-md-3">
                <input type="number" value="5" step="1" class="form-control" name="frequency" id="frequency">
              </div>
              <label for="frequency" class="col-form-label">seconds</label>
            </div>
            <div class="form-group row">
              <label for="interval" class="col-form-label">Update History:</label>
              <div class="col col-sm-6 col-md-3">
                <input type="number" value="30" step="1" class="form-control" name="interval" id="interval">
              </div>
              <label for="interval" class="col-form-label">minutes</label>
            </div>
        </form>
      </blockquote>
    </div>
  </div>
  <div class="row justify-content-center align-items-center">
    <div class="col col-lg-6 col-sm-12">
      <canvas id="h2oChart"></canvas>
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
