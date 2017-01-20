<table class="table table-striped">
    <thead>
        <tr>
            <th>Ticker</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    
<?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= $position["price"] ?></td>
        <br> 
    </tr>

<?php endforeach ?>
</table>