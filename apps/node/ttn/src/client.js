'use strict';

const mqtt = require('mqtt');
const util = require('util');
const EventEmitter = require('events');

const Client = class Client extends EventEmitter {
  constructor(broker, appEUI, appAccessKey) {
    super();
    this.client = mqtt.connect(util.format('mqtt://%s', broker), {
      username: appEUI,
      password: appAccessKey
    });
    this.client.on('connect', this._connected.bind(this));
    this.client.on('message', this._handleMessage.bind(this));
    this.client.on('error', this._error.bind(this));
  }

  end() {
    this.client.end();
  }

  _connected() {
    super.emit('connect');
    this.client.subscribe(['+/devices/+/activations', '+/devices/+/up']);
  }

  _handleMessage(topic, message) {
    var parts = topic.split('/');
    if (parts.length < 4)
      return;

    var payload = JSON.parse(message.toString());
    switch (parts[3]) {
      case 'activations':
        super.emit('activation', {
          devEUI: parts[2]
        });
        break;
      case 'up':
        super.emit('uplink', {
          devEUI: parts[2],
          fields: payload.fields || payload.payload,
          counter: payload.counter,
          metadata: payload.metadata[0]
        });
        break;
    }
  }

  _error(err) {
    super.emit('error', err);
  }
}

module.exports = Client;
