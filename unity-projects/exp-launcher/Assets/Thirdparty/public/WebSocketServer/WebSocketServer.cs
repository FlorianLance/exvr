

// system
using System.Collections.Concurrent;

// unity
using UnityEngine.Events;

namespace WebSocketServer {


    [System.Serializable]
    public class WebSocketOpenEvent : UnityEvent<WebSocketConnection> { }

    [System.Serializable]
    public class WebSocketMessageEvent : UnityEvent<WebSocketMessage> { }

    [System.Serializable]
    public class WebSocketCloseEvent : UnityEvent<WebSocketConnection> { }


    public class WebSocketServer { 
            
        // events
        public WebSocketOpenEvent onOpen = new WebSocketOpenEvent();
        public WebSocketMessageEvent onMessage = new WebSocketMessageEvent();
        public WebSocketCloseEvent onClose = new WebSocketCloseEvent();
        public ConcurrentQueue<WebSocketEvent> events = new ConcurrentQueue<WebSocketEvent>();

        public void process_events() {

            WebSocketEvent wsEvent;
            while (events.TryDequeue(out wsEvent)) {
                if (wsEvent.type == WebSocketEventType.Open) {
                    onOpen.Invoke(wsEvent.connection);
                    this.on_open(wsEvent.connection);
                } else if (wsEvent.type == WebSocketEventType.Close) {
                    onClose.Invoke(wsEvent.connection);
                    this.on_close(wsEvent.connection);
                } else if (wsEvent.type == WebSocketEventType.Message) {
                    WebSocketMessage message = new WebSocketMessage(wsEvent.connection, wsEvent.data);
                    onMessage.Invoke(message);
                    this.on_message(message);
                }
            }
        }

        public virtual void on_open(WebSocketConnection connection) {

        }

        public virtual void on_message(WebSocketMessage message) { 
        }

        public virtual void on_close(WebSocketConnection connection) { 
        }

        public virtual void on_error(WebSocketConnection connection) { 
        }
    }
}