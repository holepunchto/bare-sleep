const test = require('brittle')
const hrtime = require('bare-hrtime')
const sleep = require('.')

test('sleeps for at least the given milliseconds', (t) => {
  const start = hrtime.bigint()

  sleep(20.5)

  t.ok(hrtime.bigint() - start >= 20500000n)
})

test('sleeps for at least the given nanoseconds', (t) => {
  const start = hrtime.bigint()

  sleep.bigint(20000000n)

  t.ok(hrtime.bigint() - start >= 20000000n)
})

test('returns at once for nothing to sleep', (t) => {
  const start = hrtime.bigint()

  sleep(0)
  sleep(-1)
  sleep(NaN)
  sleep.bigint(0n)
  sleep.bigint(-1n)

  t.ok(hrtime.bigint() - start < 10000000n)
})
