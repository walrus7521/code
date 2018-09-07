
def capitalize_words(title) do
    title
    |> String.split
    |> capitalize_all
    |> join_with_whitespace
end

#IO.puts capitalize_words("the dark tower")

