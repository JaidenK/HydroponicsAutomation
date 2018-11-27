<?php
  session_start();
?>

<!DOCTYPE html>
<html lang="en">
<head>
  <title>Hydroponic Automation | Login</title>
  <meta charset="utf-8">

  <!-- Bootstrap 4 -->
  <!-- Responsive Layout -->
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>

  <!-- jQuery -->
  <!-- Powerful JavaScript library -->
  <script src="jquery-3.3.1.min.js"></script>

</head>
<body>

<!-- Nav bar to replaced by jQuery and nav.html -->
<div id="nav-placeholder"></div>
<script>$(function(){$("#nav-placeholder").load("nav.html");});</script>

<div class="container" style="margin-top:30px;margin-bottom:30px">
    <div id="login-row" class="row justify-content-center align-items-center">
        <div id="login-column" class="col-md-6">
            <div class="box">
                <div class="float">
                    <form class="form" action="">
                        <div class="form-group">
                            <label for="username">Username:</label><br>
                            <input type="text" name="username" id="username" class="form-control">
                        </div>
                        <div class="form-group">
                            <label for="password">Password:</label><br>
                            <input type="text" name="password" id="password" class="form-control">
                        </div>
                        <div class="form-group">
                            <input type="submit" name="submit" class="btn btn-info btn-md" value="Login">
                        </div>
                        <div>
                          <a href="/reset.php">Forgot password?</a>
                        </div>
                        <div>
                          <a href="/signup.php">Create new account</a>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>
</div>


<!-- Footer to replaced by jQuery and footer.html -->
<div id="footer-placeholder"></div>
<script>$(function(){$("#footer-placeholder").load("footer.html");});</script>



<!-- https://bootsnipp.com/snippets/featured/login-form -->
</body>
</html>
