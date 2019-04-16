<nav class="navbar navbar-expand-sm bg-dark navbar-dark">
  <a class="navbar-brand" href="index.php">Hydroponic Automation</a>
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#collapsibleNavbar">
    <span class="navbar-toggler-icon"></span>
  </button>
  <div class="collapse navbar-collapse" id="collapsibleNavbar">
    <ul class="navbar-nav">
      <li class="nav-item">
        <a class="nav-link" href="/goals.php">Goals</a>
      </li>
      <!--<li class="nav-item">
        <a class="nav-link" href="#">Link</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="#">Link</a>
      </li>  -->  
    </ul>
    <?php
      // Test all three situations because apparently it errors when the session isn't started
      if (session_id() == "" or !array_key_exists('isLoggedIn', $_SESSION) or !$_SESSION["isLoggedIn"]) {
        echo' 
          <ul class="navbar-nav ml-auto" id="navLoggedOut">
            <li class="nav-item">
                <a class="nav-link" href="/login.php">Login</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="/signup.php">Register</a>
            </li>
          </ul>
        ';
      }else{
        echo '
          <ul class="navbar-nav ml-auto" id="navLoggedIn">
            <li class="nav-item">
                <a class="nav-link" href="/logout.php">Logout</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="/controlPanel.php">Control Panel</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="/detailedGraphs.php">History Graphs</a>
            </li>
            <li class="navbar-text" id="navUsername">
                Username
            </li>
          </ul>
        ';
      }
    ?>
  </div>  
</nav>
