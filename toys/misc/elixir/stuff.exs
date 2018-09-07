
# run: elixir stuff.exs

defmodule ModuleName do
  def hello do
    IO.puts "Hello World"
  end
end

defmodule Math do
  def sum(a, b) do
    a + b
  end
end

IO.puts Math.sum(1, 2)
IO.puts ModuleName.hello()

