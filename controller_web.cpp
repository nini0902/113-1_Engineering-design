<!DOCTYPE html>
<html>
<head>
  <title>Car Control</title>
  <style>
    body {
      font-family: Arial;
      text-align: center;
      margin-top: 50px;
    }
    .button-container {
      display: flex;
      flex-direction: row;
      justify-content: center;
      align-items: center;
    }
    button {
      width: 100px;
      height: 50px;
      margin: 10px;
      font-size: 16px;
    }
  </style>
</head>
<body>
  <h1>NodeMCU Car Control</h1>
  <div class="button-container">
    <button onclick="sendCommand('forward')">Forward</button>
  </div>
  <div class="button-container">
    <button onclick="sendCommand('left')">Left</button>
    <button onclick="sendCommand('stop')">Stop</button>
    <button onclick="sendCommand('right')">Right</button>
  </div>
  <div class="button-container">
    <button onclick="sendCommand('backward')">Backward</button>
  </div>
  <script>
    function sendCommand(cmd) {
      fetch('/' + cmd) // 使用 Fetch 發送 AJAX 請求
        .then(response => {
          if (!response.ok) {
            throw new Error('Network response was not ok');
          }
          return response.text();
        })
        .then(data => console.log(data)) // 打印伺服器回應
        .catch(error => console.error('Error:', error));
    }
  </script>
</body>
</html>
