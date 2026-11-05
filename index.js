const binding = require('./binding')

module.exports = exports = function sleep(ms) {
  if (ms > 0) binding.sleep(BigInt(Math.ceil(ms * 1e6)))
}

exports.bigint = function sleep(ns) {
  if (ns > 0n) binding.sleep(ns)
}
