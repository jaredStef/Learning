<?php
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("deposit_form.php");
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO: Add revious REGEX 
        // check if post is a valid int 
        $balance = CS50::query("SELECT * FROM `users` WHERE id={$_SESSION["id"]}")[0]["cash"];
        
        if (!preg_match("/^\d+$/", $_POST["amount"]))
        {
            apologize("Please enter a valid number"); 
        }
        else 
        {
            //TODO INSERT VALID VARIABLE
          $cash = CS50::query("SELECT * FROM `users` WHERE id={$_SESSION["id"]}")[0]["cash"];
          $cash += $_POST["amount"]; 
          CS50::query("UPDATE `users` SET cash={$cash} WHERE id={$_SESSION["id"]};");  
          $_SESSION["amount"] = $_POST["amount"];; 
          $_SESSION["bal"] = $cash; 
          render("deposit_success.php", ["title" => "Success!"]);
        }
    }
?>