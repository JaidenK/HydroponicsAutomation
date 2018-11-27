<nav class="navbar navbar-expand-sm bg-dark navbar-dark">
  <a class="navbar-brand" href="index.php">Hydroponic Automation</a>
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#collapsibleNavbar">
    <span class="navbar-toggler-icon"></span>
  </button>
  <div class="collapse navbar-collapse" id="collapsibleNavbar">
    <ul class="navbar-nav">
      <li class="nav-item">
        <a class="nav-link" href="/goals.html">Goals</a>
      </li>
      <!--<li class="nav-item">
        <a class="nav-link" href="#">Link</a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="#">Link</a>
      </li>  -->  
    </ul>
    <ul class="navbar-nav ml-auto" id="navLoggedOut">
      <li class="nav-item">
          <a class="nav-link" href="/login.php">Login</a>
      </li>
      <li class="nav-item">
          <a class="nav-link" href="/signup.php">Register</a>
      </li>
      <!-- TODO: Make this change if they're logged in. -->
    </ul>
    <ul class="navbar-nav ml-auto" id="navLoggedIn">
      <li class="nav-item">
          <a class="nav-link" href="/controlPanel.php">Control Panel</a>
      </li>
      <li class="navbar-text" id="navUsername">
          Username
      </li>
    </ul>
  </div>  
</nav>
<script type="text/javascript">
$(document).ready(function(){
    if(test) {
      $("#navLoggedIn").show();
      $("#navLoggedOut").hide();
    }else{
      $("#navLoggedIn").hide();
      $("#navLoggedOut").show();
    }
});
</script>
