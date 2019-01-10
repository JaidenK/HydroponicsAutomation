<?php
  session_start();
  
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <title>Hydroponic Automation | Home</title>
  <?php include 'header.php'; ?>

  <style>
    .video-container {
      position:relative;
      padding-bottom:56.25%;
      padding-top:30px;
      height:0;
      overflow:hidden;
    }
    .video-container video {
      position:absolute;
      top:0;
      left:0;
      width:100%;
      height:100%;
    }
  </style>
</head>
<body>

<!-- Navbar -->
<?php include 'nav.php'; ?>

<div class="container" style="margin-top:30px">
  <div class="row">
    <div class="col-sm-4">
      <h2>About the Project</h2>
      <h5>Problem:</h5>
      <p>Fresh water on Earth is a limited resource, and traditional farming is the largest consumer of fresh water. Growing crops with hydroponics uses a fraction of the water, but increases the complexity to the growing process.</p>
      <h5>Solution:</h5>
      <p>Automation can reduce hydroponics' barriers to entry, allowing more growers to switch to hydroponics and save water. We aim to automate the tasks of monitoring and controlling the system vitals, such as pH and nutrient levels, so that no user interaction is required between planting a seedling and harvesting.</p>
      <h3>Some Links</h3>
      <ul class="nav nav-pills flex-column">
        <li class="nav-item">
          <a class="nav-link" href="https://github.com/JaidenK/HydroponicsAutomation" target="_blank">Git Repo</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="https://sdp.soe.ucsc.edu/sdp/projects/478" target="_blank">SOE Project Webpage</a>
        </li>
        <!--
        <li class="nav-item">
          <a class="nav-link" href="#">Link</a>
        </li>
        <li class="nav-item">
          <a class="nav-link disabled" href="#">Disabled</a>
        </li>
      -->
      </ul>
      <hr class="d-sm-none">
    </div>
    <div class="col-sm-8">
      <h2>Greenlight</h2>
      <h5>Project approved, Nov 20, 2018</h5>
      <p>After meeting with Gabriel Elkaim and Max Dunne, the Hydroponics Automation project was approved for a team of 4.</p>
      <br>
      <h2>Project Pitch</h2>
      <h5>In-class presentation, Oct 30, 2018</h5>
      <p>
        <div class="video-container">
          <video width="1280" height="720" controls>
            <source src="media/video/HydroPitch.mp4" type="video/mp4">
            Your browser does not support the video tag.
          </video>
        </div>
      </p>
    </div>
  </div>
</div>

<!-- Footer to replaced by jQuery and footer.html -->
<div id="footer-placeholder"></div>
<script>$(function(){$("#footer-placeholder").load("footer.html");});</script>

<script type="text/javascript">
  $(document).ready(function(){
    // alert(test);
  });
</script>

</body>
</html>
