


/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2024] [Florian Lance][Auxime]                                   **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System;
using System.Net.WebSockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Ex {

    public class WebsocketComponent : ExComponent {

        private async Task connect_async() {
            var uri = new Uri("ws://localhost:9006");
            var ws = new ClientWebSocket();
            await ws.ConnectAsync(uri, CancellationToken.None);
        }
        protected override bool initialize() {

            var task = Task.Run(async () => await connect_async());
            task.Wait();
            //var result = task.WaitAndUnwrapException();
            //var result = AsyncContext.Run();

            return true;
        }


        protected override void update() {
            //byte[] buffer = new byte[1024];
            //while (ws.State == WebSocketState.Open) {
            //    var result = await ws.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);

            //    if (result.MessageType == WebSocketMessageType.Close) {
            //        await ws.CloseAsync(WebSocketCloseStatus.NormalClosure, "Client closing.", CancellationToken.None);
            //        break;
            //    } else {
            //        Console.WriteLine($"Received {result.Count} bytes:");
            //        Console.WriteLine(Encoding.UTF8.GetString(buffer, 0, result.Count));
            //    }
            //}
        }
    }

}

//using System.Net.WebSockets;
//using System.Text;

//using var ws = new ClientWebSocket();

//var uri = new Uri("ws://localhost:9006");
//await ws.ConnectAsync(uri, CancellationToken.None);

//Console.WriteLine("Connected");

//var message = "Hello from client!";
//var buffer = Encoding.UTF8.GetBytes(message);
//await ws.SendAsync(new ArraySegment<byte>(buffer), WebSocketMessageType.Text, true, CancellationToken.None);

//var receiveBuffer = new byte[1024];
//var receiveResult = await ws.ReceiveAsync(new ArraySegment<byte>(receiveBuffer), CancellationToken.None);
//var receivedMessage = Encoding.UTF8.GetString(receiveBuffer, 0, receiveResult.Count);

//Console.WriteLine($"Received message: {receivedMessage}");