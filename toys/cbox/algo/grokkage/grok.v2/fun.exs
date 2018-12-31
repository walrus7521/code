
def capitalize_words(title) do
    title
    |> String.split
    |> capitalize_all
    |> join_with_whitespace
end

title = capitalize_words("the dark tower")
IO.inspect title


