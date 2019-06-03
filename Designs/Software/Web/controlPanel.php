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

  $sql = 'SELECT * FROM TestTable ORDER BY `time` DESC LIMIT 1';
  $result = mysqli_query($conn,$sql);
  if(!$result) {
    die('Could not get data: ' . mysqli_error($conn));
  }
  // Why are the timestamps 7 hours off?
  $sevenHours = 25200;
  $i = 0;
  while($row=mysqli_fetch_array($result,MYSQLI_ASSOC)) {
    // $h2o_level[$i] = new Point(strtotime($row['time'])-$now+$sevenHours,$row['h2o_level']);
    $allData["h2o_level"][$i] = new Point($row['time'],$row['h2o_level']);
    $allData["ph_level"][$i] = new Point($row['time'],$row['ph_level']);
    $allData["ph_target"][$i] = new Point($row['time'],$row['ph_target']);
    $allData["ec_level"][$i] = new Point($row['time'],$row['ec_level']);
    $allData["ec_target"][$i] = new Point($row['time'],$row['ec_target']);
    $allData["flow_measured"][$i] = new Point($row['time'],$row['flow_measured']);
    $allData["flow_target"][$i] = new Point($row['time'],$row['flow_target']);
    $allData["temp_measured"][$i] = new Point($row['time'],$row['temp_measured']);
    $allData["temp_target"][$i] = new Point($row['time'],$row['temp_target']);

    $allData["ph_up_stored"][$i] = new Point($row['time'],$row['ph_up_stored']);
    $allData["ph_down_stored"][$i] = new Point($row['time'],$row['ph_down_stored']);
    $allData["ec_stored"][$i] = new Point($row['time'],$row['ec_stored']);
    $allData["h2o_stored"][$i] = new Point($row['time'],$row['h2o_stored']);
    $allData["h2o_target"][$i] = new Point($row['time'],$row['h2o_target']);
    $i++;
  }

  $settingsData = [];
  $sql = "SELECT * FROM `MachineConfig` WHERE `MachineConfig`.`ProductID`='ABCD1234EFGH5678'";
  $result = mysqli_query($conn,$sql);
  if(!$result) {
    die('Could not get data: ' . mysqli_error($conn));
  }
  while($row=mysqli_fetch_array($result,MYSQLI_ASSOC)) {
    $settingsData["phoneStr"] = $row["phoneStr"];
    $settingsData["carrierStr"] = $row["carrierStr"];
    $settingsData["emailStr"] = $row["emailStr"];
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
    var numCharts = 0;
    var settingsData = {
      phone:<?php echo "'".$settingsData["phoneStr"]."'"; ?>,
      carrier:<?php echo "'".$settingsData["carrierStr"]."'"; ?>,
      email:<?php echo "'".$settingsData["emailStr"]."'"; ?>,
    };
    function newTopPageTargetChart(label, meas, targ, max){
      $("#targetChartsDiv").append("<span><canvas style='width:100px;height:300px;display: inline;' id='targetChart"+(++numCharts)+"'></canvas></span>")

      var myChart = new Chart($("#targetChart"+numCharts), {
        type: 'bar',
        data: {
          labels: [label],
          datasets: [{
            label: 'Measured',
            backgroundColor: ["#66FF66"],
            data: [meas]
          },{
            label: 'Target',
            backgroundColor: ["#DDFFDD"],
            data: [targ]
          }]
        },
        options: {
          responsive: false,
          maintainAspectRatio: false,
          title: {
            display: false
          },
          legend: {
            display: false
          },
          scales: {
            yAxes: [{
              ticks: {
                min: 0,
                max: max
              }
            }]
          }
        }
      });
    }

    $(document).ready(function(){
      newTopPageTargetChart("Water Level",<?php echo $allData["h2o_level"][0]->y ?>,<?php echo $allData["h2o_target"][0]->y ?>,17); // max: 17cm
      newTopPageTargetChart("pH",<?php echo $allData["ph_level"][0]->y ?>,<?php echo $allData["ph_target"][0]->y ?>,14); // max: 14 pH
      newTopPageTargetChart("EC",<?php echo $allData["ec_level"][0]->y ?>,<?php echo $allData["ec_target"][0]->y ?>,4000);
      newTopPageTargetChart("Flow",<?php echo $allData["flow_measured"][0]->y ?>,<?php echo $allData["flow_target"][0]->y ?>,4); // max: 4 LPM
      newTopPageTargetChart("Temp",<?php echo $allData["temp_measured"][0]->y ?>,<?php echo $allData["temp_target"][0]->y ?>,110); // 
      
      var phUpCtx = $("#phUpChart");
      var phUpChart = new Chart(phUpCtx, {
        type: 'doughnut',
        data: {
          labels: ["",""],
          datasets: [{
            backgroundColor: ["#66FF66", "#DDFFDD"],
            data: [<?php $x = $allData["ph_up_stored"][0]->y; printf("%f, %f",$x,100-$x); ?>]
          }]
        },
        options: {
          title: {
            display: true,
            text: "pH Up"
          },
          legend: {
            display: false
          }
        }
      });
      var phDownCtx = $("#phDownChart");
      var phDownChart = new Chart(phDownCtx, {
        type: 'doughnut',
        data: {
          labels: ["",""],
          datasets: [{
            backgroundColor: ["#FF6666", "#FFDDDD"],
            data: [<?php $x = $allData["ph_down_stored"][0]->y; printf("%f, %f",$x,100-$x); ?>]
          }]
        },
        options: {
          title: {
            display: true,
            text: "pH Down"
          },
          legend: {
            display: false
          }
        }
      });
      var ecCtx = $("#ecChart");
      var ecChart = new Chart(ecCtx, {
        type: 'doughnut',
        data: {
          labels: ["",""],
          datasets: [{
            backgroundColor: ["#FFDD66", "#FFFFDD"],
            data: [<?php $x = $allData["ec_stored"][0]->y; printf("%f, %f",$x,100-$x); ?>]
          }]
        },
        options: {
          title: {
            display: true,
            text: "Nutrients"
          },
          legend: {
            display: false
          }
        }
      });
      var waterCtx = $("#waterChart");
      var waterChart = new Chart(waterCtx, {
        type: 'doughnut',
        data: {
          labels: ["",""],
          datasets: [{
            backgroundColor: ["#6666FF", "#DDDDFF"],
            data: [<?php $x = $allData["h2o_stored"][0]->y; printf("%f, %f",$x,100-$x); ?>]
          }]
        },
        options: {
          title: {
            display: true,
            text: "Water Resevoir"
          },
          legend: {
            display: false
          }
        }
      });
      $('#editTargetsForm').submit(function(e){
        // https://www.airpair.com/js/jquery-ajax-post-tutorial
        $("#editTargetsSaveButton").html('Saving...');
        $.post(
          'setTargets.php',
          $(this).serialize(),
          function( data, textStatus, jQxhr ){
            if(data=="success") {
              $("#editTargetsSaveButtonResponse").html("Settings saved!");
              $("#editTargetsSaveButtonResponse").removeClass("text-danger");
              $("#editTargetsSaveButtonResponse").addClass("text-primary");
            }else{
              $("#editTargetsSaveButtonResponse").html("Unable to save settings.");
              $("#editTargetsSaveButtonResponse").addClass("text-danger");
              $("#editTargetsSaveButtonResponse").removeClass("text-primary");
              console.log(data);
            }
            $("#editTargetsSaveButtonResponse").show();
          },
          'text'
        ).fail(function() {
          alert( "Could not update targets." );
        }).always(function(){
          $("#editTargetsSaveButton").html('Save Changes');
          setTimeout(function(){
            $("#editTargetsSaveButtonResponse").fadeOut();
          }, 1000);
        });

        e.preventDefault();
      });
      
      $('#editSettingsForm').change(function(e) {
        if($('#editSettingsForm')[0].checkValidity()) {
          $('#editSettingsSaveButton').attr("disabled", false);
          settingsData.email = $('#inputEmail').val();
          settingsData.phone = $('#inputPhone').val();
          settingsData.carrier = $('#inputCarrier').val();
          $('#cellText').html(settingsData.phone.replace(/-/g,"") + settingsData.carrier);
          $('#emailText').html(settingsData.email);
        }else{
          $('#editSettingsSaveButton').attr("disabled", true);
        }
      }).submit(function(e){
        if($('#editSettingsForm')[0].checkValidity()) {
          // https://www.airpair.com/js/jquery-ajax-post-tutorial
          $("#editSettingsSaveButton").html('Saving...');
          $.post(
            'setSettings.php',
            $(this).serialize(),
            function( data, textStatus, jQxhr ){
              if(data=="success") {
                alert("Settings updated.");
              }else{
                alert("Settings could not be updated.");
                console.log(data);
              }
            },
            'text'
          ).fail(function() {
            alert( "Could not update settings." );
          }).always(function(){
            $("#editSettingsSaveButton").html('Save Changes');
          });
        }
        e.preventDefault();
      });
      $("#testNotificationsButton").click(function(e){
        $.post(
            'setSettings.php',
            "TestNotify=1",
            function( data, textStatus, jQxhr ){
              if(data=="notified") {
                alert("Notification sent.");
              }else{
                alert("An error occurred while sending the notification.");
                console.log(data);
              }
            },
            'text'
          ).fail(function() {
            alert("An error occurred while sending the notification.");
          });
      });

      // Populate forms with current values
      $('#inputEmail').val(settingsData.email);
      $('#inputPhone').val(settingsData.phone);
      $('option[value="' + settingsData.carrier + '"]').attr('selected',true);
      $('#cellText').html(settingsData.phone.replace(/-/g,"") + settingsData.carrier);
      $('#emailText').html(settingsData.email);

      // Enables all tooltips on the page
      $('[data-toggle="tooltip"]').tooltip();
    });
  </script>
</head>
<body>

<!-- Navbar -->
<?php include 'nav.php'; ?>

<div class="container" style="margin-top:30px;margin-bottom:30px">
    <div class="row justify-content-center align-items-center">
      <div class="col col-lg-6 col-sm-12">
        <div id="targetChartsDiv"></div>
        <button type="button" class="btn btn-primary" data-toggle="modal" data-target="#targetEditModal">Edit Targets</button>
        <button type="button" class="btn btn-primary" data-toggle="modal" data-target="#settingsEditModal">Edit Settings</button>
      </div>
      <div class="col col-lg-6 col-sm-12">
        <div class="row justify-content-center">
          Storage Levels
        </div>
        <div class="row">
          <div class="col col-lg-6">
            <canvas id="phUpChart"></canvas>
          </div>
          <div class="col col-lg-6">
            <canvas id="phDownChart"></canvas>
          </div>
          <div class="col col-lg-6">
            <canvas id="ecChart"></canvas>
          </div>
          <div class="col col-lg-6">
            <canvas id="waterChart"></canvas>
          </div>
        </div>
      </div>
    </div>
</div>


<!-- Footer to replaced by jQuery and footer.html -->
<div id="footer-placeholder"></div>
<script>$(function(){$("#footer-placeholder").load("footer.html");});</script>



<!-- Modal for editing targets -->
<div class="modal" id="targetEditModal" tabindex="-1" role="dialog">
  <div class="modal-dialog modal-dialog-centered" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" data-toggle="tooltip" title="TODO: Populate the form with the existing targets, enable dropdown form for populating with presets">Edit Targets</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <form id="editTargetsForm">
        <div class="modal-body">
          <label for="exampleFormControlFile1">Profile</label>
          <select class="form-control" id="targetPresetsProfile">
            <option>Custom</option>
            <option disabled>Lettuce</option>
            <option disabled>Spinach</option>
            <option disabled>"Spinach"</option>
          </select>
          <hr>
          <div class="form-group row">
            <label for="inputWaterLevel" class="col-sm-3 col-form-label">Water Level</label>
            <div class="col-sm-9">
              <input type="number" step="0.01" class="form-control" name="water" id="inputWaterLevel" placeholder="Centimeters">
            </div>
          </div>
          <div class="form-group row">
            <label for="inputPH" class="col-sm-3 col-form-label">pH</label>
            <div class="col-sm-9">
              <input type="number" step="0.01" class="form-control" name="ph" id="inputPH" placeholder="pH">
            </div>
          </div>
          <div class="form-group row">
            <label for="inputEC" class="col-sm-3 col-form-label">EC</label>
            <div class="col-sm-9">
              <input type="number" step="0.01" class="form-control" name="ec" id="inputEC" placeholder="EC">
            </div>
          </div>
          <div class="form-group row">
            <label for="inputFlow" class="col-sm-3 col-form-label">Flow</label>
            <div class="col-sm-9">
              <input type="number" step="0.01" class="form-control" name="flow" id="inputFlow" placeholder="L/min">
            </div>
          </div>
          <div class="form-group row">
            <label for="inputTemp" class="col-sm-3 col-form-label">Temp</label>
            <div class="col-sm-9">
              <input type="number" step="0.01" class="form-control" name="temp" id="inputTemp" placeholder="Degrees Frankenstein">
            </div>
          </div>
        </div>
        <input type="hidden" id="inputProductId" name="ProductID" value="ABCD1234EFGH5678">
        <div class="modal-footer">
          <span id="editTargetsSaveButtonResponse" class="text-primary" style="display:none"></span>
          <button type="submit" id="editTargetsSaveButton" class="btn btn-primary">Save changes</button>
          <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
        </div>
      </form>
    </div>
  </div>
</div>



<!-- Modal for editing settings -->
<div class="modal" id="settingsEditModal" tabindex="-1" role="dialog">
  <div class="modal-dialog modal-dialog-centered" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" data-toggle="tooltip" title="TODO: Remove TODO message">Edit Settings</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <form id="editSettingsForm">
        <div class="modal-body">
          <div class="form-group row">
            <label for="inputEnableNotif" class="col-sm-3 col-form-label">Notifications</label>
            <div class="col-sm-9">
              <input type="radio" name="notifEnable" value="enabled" checked> Enabled<br/>
              <input type="radio" name="notifEnable" value="disabled" disabled> Disabled
            </div>
          </div>
          <div class="form-group row">
            <label for="inputEmail" class="col-sm-3 col-form-label">e-mail</label>
            <div class="col-sm-9">
              <input type="email" class="form-control" name="email" id="inputEmail" placeholder="foo@bar.com">
            </div>
          </div>
          <div class="form-group row">
            <label for="inputPhone" class="col-sm-3 col-form-label">phone</label>
            <div class="col-sm-9">
              <input type="tel" class="form-control" name="phone" pattern="[0-9]{3}-[0-9]{3}-[0-9]{4}" id="inputPhone" placeholder="800-867-5309">
            </div>
          </div>
          <label for="exampleFormControlFile1">Carrier</label>
          <select class="form-control" id="inputCarrier" name="carrier">
            <option value="@vzwpix.com">Verizon</option>
            <option value="@tmomail.net">T-Mobile</option>
            <option disabled>AT&amp;T</option>
            <option disabled>Sprint</option>
            <option disabled>"Spinach"</option>
          </select>
          <div class="row">
            <div class="col col-sm-12">
              <i id="cellText">8052318038@vzwpix.com</i><br/>
              <i id="emailText">jaaking@ucsc.edu</i>
            </div>
          </div>
          <div class="row">
            <div class="col col-sm-12">
              <button type="button" class="btn btn-primary" data-toggle="modal" data-target="#testNotifications" id="testNotificationsButton">Send Test Notifcation</button>
            </div>
          </div>
          <hr>
          <div class="modal-footer">
            <span id="editSettingsSaveButtonResponse" class="text-primary" style="display:none"></span>
            <button type="submit" id="editSettingsSaveButton" class="btn btn-primary">Save changes</button>
            <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
        </div>
      </form>
    </div>
  </div>
</div>




<!-- https://bootsnipp.com/snippets/featured/login-form -->
</body>
</html>
