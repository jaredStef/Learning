<?php
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php"); 
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        $ticker = strtoupper($_POST["ticker"]); 
        $shareCount = $_POST["shareCount"];
        $sharePrice = lookup($ticker)["price"]; 
        $cost = $sharePrice * $shareCount; 
        $balance =  CS50::query("SELECT * FROM `users` WHERE id={$_SESSION["id"]}")[0]["cash"];
        
        if (!preg_match("/^\d+$/", $shareCount))
        {
            apologize("Please enter a valid number"); 
        }
        else if ($sharePrice == NULL)
        {
            apologize("\"{$ticker}\" is not a valid stock"); 
        }
        else if ($balance < $cost)
        {
            apologize("Insufficent funds: You are ${$cost - $balance} short"); 
        }
        else 
        {
            CS50::query("INSERT INTO `portfolios` (userId, symbol, shares) VALUES({$_SESSION["id"]}, \"{$ticker}\", {$shareCount}) ON DUPLICATE KEY UPDATE shares = shares + {$shareCount};");
            
            $newBalance = $balance - $cost; 
            
           CS50::query("UPDATE `users` SET cash={$newBalance} WHERE id={$_SESSION["id"]};");
            
            $_SESSION["shares"] = $shareCount;
            $_SESSION["ticker"] = $ticker;
            $_SESSION["price"] = $cost;
            $_SESSION["bal"] = $newBalance;
            
            CS50::query("INSERT INTO `history` (action, symbol, shares, price, date, userId) VALUES (\"BUY\", \"{$ticker}\", {$shareCount},
        {$cost}, CURRENT_TIMESTAMP, {$_SESSION["id"]});");
            
            render("buy_success.php", ["title" => "Purchased!"]); 
        }
    }
?>