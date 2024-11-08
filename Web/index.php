<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Parking Manager</title>
    <link rel="shortcut icon" href="./img/HUNRE_Logo.png" type="image/x-icon">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.2.1/css/all.min.css">
    <link rel="stylesheet" href="./font.css">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        html {
            font-family: Arial, Helvetica, sans-serif;
        }

        #header {
            width: 100%;
            height: 100px;
            position: relative;
            background-color: #223771;
            text-align: center;
            color: #fff;
            line-height: 100px;
        }

        #header img {
            margin: 10px;
            height: 80px;
            width: auto;
            float: left;
        }

        .taskbar {
            width: 10%;
            position: relative;
            height: 639px;
            background-color: #223771;
        }

        .taskbar>li {
            width: 100%;
            height: 50px;

        }

        .taskbar li a:hover {
            color: orangered;
            background-color: #ccc;
        }

        .taskbar>li>a {
            display: block;
            height: 100%;
            text-decoration: none;
            color: #96aae0;
            padding-top: 15px;
            padding-left: 7px;
        }

        .pdright4 {
            padding-right: 4px;
        }

        #body {
            background-color: rgb(161, 161, 189);
        }

        #wapper {
            position: absolute;
            width: 88%;
            height: 600px;
            background-color: #fff;
            top: 100px;
            right: 15px;
            border-radius: 20px;
            margin-top: 10px;
            padding-top: 10px;
        }

        #table-container {
            overflow-y: scroll;
            width: 90%;
            height: 580px;
            margin: 0 auto;
        }

        #table-container table {
            width: 100%;
            border-collapse: collapse;
            background-color: #fff;
            border: 1px solid #ccc;
            text-align: center;
        }

        #table-container table th {
            background-color: rgba(85, 86, 107, 1);
            color: #fff;
            font-weight: bold;
            padding: 10px;
        }

        #table-container table tr {
            border: 1px solid #ccc;
        }

        #table-container table td {
            padding: 10px;
        }

        .sticky-thead {
            position: sticky;
            top: 0;
            z-index: 1;
        }

        .table-header {
            padding-left: 20px;
            padding-bottom: 20px;
        }
    </style>
    <script src="jquery.min.js"></script>
    <script>
        function sendSignal(signal) {
            $.ajax({
                url: 'send_signal.php',
                type: 'GET',
                data: {
                    signal: signal
                },
                success: function(response) {
                    console.log('Signal sent: ' + signal);
                },
                error: function(xhr, status, error) {
                    console.error('Error sending signal: ' + error);
                }
            });
        }

        $(document).ready(function() {
            setInterval(function() {
                loadData();
            }, 100);
        });

        function loadData() {
            $.ajax({
                url: 'get_data.php',
                type: 'POST',
                success: function(data) {
                    $('#data').html(data);
                }
            });
        }
    </script>
</head>

<body>
    <div id="main">
        <div id="header">
            <img src="./img/HUNRE_Logo.png" alt="">
            <h1>SMART PARKING MANAGER</h1>
        </div>
        <div id="body">
            <ul class="taskbar">
                <li><a href="index.php"><i class='fa-solid fa-house pdright4'></i>Home</a></li>
                <li><a href="#" onclick="sendSignal(2); window.location.href='card.php'; return false;"><i class='fa-solid fa-credit-card pdright4'></i>Card</a></li>
                <li><a href="search.php"><i class='fa-solid fa-search pdright4'></i>Tìm kiếm</a></li>
                <li><a href="info.php"><i class='fa fa-info-circle pdright4'></i>Thông Tin</a></li>
            </ul>
            <div id="wapper">
                <div id="table-container">
                    <table>
                        <thead class="sticky-thead">
                            <tr>
                                <th>STT</th>
                                <th>Mã thẻ</th>
                                <th>Trạng thái</th>
                                <th>Thời gian</th>
                            </tr>
                        </thead>
                        <tbody id="data">
                            <!-- Dữ liệu sẽ được cập nhật qua Ajax -->
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
</body>

</html>