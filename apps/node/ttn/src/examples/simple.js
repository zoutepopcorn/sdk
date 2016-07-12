var ttn = require('..');

var appEUI = '<insert AppEUI>';
var accessKey = '<insert App Access Key>';
var client = new ttn.Client('staging.thethingsnetwork.org', appEUI, accessKey);

client.on('connect', function() {
  console.log('connected');
});

client.on('uplink', function (msg) {
  console.log('uplink', msg)

  // These are messages sent by devices on The Things Network
  // msg = {
  //   devEUI: '00000000973572D0',
  //   fields: { /* ... */ },
  //   counter: 44,
  //   metadata: { /* ... */ },
  // }

  // Schedule a reply
  var payload = new Buffer('01AB', 'hex')
  client.downlink(msg.devEUI, payload, '1h', 1)
})

client.on('activation', function (evt) {
  console.log('activation', evt)

  // These are devices that are activated on The Things Network
  // evt = {
  //   devEUI: '00000000973572D0',
  // }
})

client.on('error', function (err) {
  console.log('error', err)

  // TODO: Handle error
})