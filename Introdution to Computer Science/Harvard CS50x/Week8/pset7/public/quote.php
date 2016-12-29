<?php

    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("requestQuote.php", ["title" => "Quote"]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["quote"]); 
        
        if ($stock["symbol"] == NULL)
        {
            apologize("The ticker \"{$_POST["quote"]}\" could not be found");
        }
        else 
        {
            $_SESSION["symbol"] = $stock["symbol"];
            $_SESSION["name"]   = $stock["name"];
            $_SESSION["price"]  = $stock["price"];
            render("viewQuote.php", ["title" => "Quote"]);    
        }
        
    }
?>