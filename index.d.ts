/**
 * Blocks the calling thread for at least `ms` milliseconds, which may be
 * fractional. Nothing else runs on the thread meanwhile, its event loop
 * included.
 * @param ms - The number of milliseconds to sleep for.
 */
declare function sleep(ms: number): void

declare namespace sleep {
  /**
   * Blocks the calling thread for at least `ns` nanoseconds.
   * @param ns - The number of nanoseconds to sleep for.
   */
  export function bigint(ns: bigint): void
}

export = sleep
