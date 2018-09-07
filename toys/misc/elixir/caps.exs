
defmodule ModName do
  def caps(title) do
    title
    |> String.split.capitalize
#    |> capitalize(title)
#    |> join_with_whitespace
  end
end

IO.puts ModName.caps("the dark tower")

