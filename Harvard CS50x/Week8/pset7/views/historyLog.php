<table class="table table-striped">
    <thead>
        <tr>
            <th>Date & Time</th>
            <th>Order</th>
            <th>Ticker</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    
    <tbody>
    <?php foreach ($_SESSION["history"] as $item): ?>
        <tr>
            <td><?= $item["date"] ?></td>
            <td><?= $item["action"] ?></td>
            <td><?= $item["symbol"] ?></td>
            <td><?= $item["shares"] ?></td>
            <td><?= $item["price"] ?></td>
            <br> 
        </tr>
    <?php endforeach ?>
    </tbody>
</table>

<?php
    if ($_SESSION["history"] == NULL)
    {
        echo "<p>No History</p>";
    }
?>