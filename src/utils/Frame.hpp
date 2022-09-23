#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>

// capture reference by reference in a lambda
// reference: https://stackoverflow.com/a/21443273
std::function<void()> computeNextIterationLambda(Grid &grid)
{
  const auto gridPtr = &grid;
  return [gridPtr]
  { gridPtr->computeNextIteration(); };
}

// the C++ version of JavaScript setInterval
// repeatedly calls a function or executes a code snippet, with a fixed time delay between each call
// JavaScript setInterval: https://developer.mozilla.org/en-US/docs/Web/API/setInterval
// reference: https://stackoverflow.com/a/72226772
template <typename F>
void setInterval(F fun, std::chrono::steady_clock::duration interval, std::shared_ptr<std::atomic_bool> cancel_token = nullptr)
{
  std::thread([fun = std::move(fun), interval, tok = std::move(cancel_token)]()
              { 
    // Call until token becomes true (if it is set)
    while (!tok || !*tok) 
    { 
      auto next = std::chrono::steady_clock::now() + interval;
      fun();
      std::this_thread::sleep_until(next);
    } })
      .detach();
}
