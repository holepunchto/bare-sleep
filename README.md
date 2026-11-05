# bare-sleep

Blocking sleep for JavaScript.

```
npm i bare-sleep
```

## Usage

```js
const sleep = require('bare-sleep')

sleep(20) // blocks for 20 milliseconds
sleep.bigint(20000000n) // blocks for 20000000 nanoseconds
```

## Threat model

`bare-sleep` is one of the addons Bare compiles into its binary, so it inherits [Bare's threat model](https://github.com/holepunchto/bare/blob/main/docs/threat-model.md). See [`docs/threat-model.md`](docs/threat-model.md) for where this addon sits in it.

## License

Apache-2.0
