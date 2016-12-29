<?php
    require("../includes/config.php");
    
    $histroy = CS50::query("SELECT * from `history` WHERE userID={$_SESSION["id"]} ORDER BY date DESC;");
    $_SESSION["history"] = $histroy;
    
    render("historyLog.php", ["title" => "History"])
?>