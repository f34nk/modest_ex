defmodule ModestExFindTest do
  use ExUnit.Case
  doctest ModestEx

  test "all selectors from file" do
  
    File.open("test/fixtures/find.csv", [:read], fn(file) ->
      IO.binstream(file, :line)
      |> Stream.map(fn(line) ->
        matched = Regex.run(~r/^(0|1);(.*);(.*);(.*)$/, line)
        cond do
          matched != nil && Enum.count(matched) == 5 && Enum.at(matched, 1) == "1" ->
            selector = Enum.at(matched, 2)
            input = Enum.at(matched, 3)
            output = Enum.at(matched, 4)
            output = cond do
              String.contains?(output, "|") -> String.split(output, "|")
              true -> output
            end
            case ModestEx.find(input, selector) do
              {:error, _} ->
                raise RuntimeError,
                  "\n\tpattern: " <> selector <>
                  "\n\tinput: " <> input
                  # "\n\texpected: " <> Enum.join(output, "|")
              reply ->
                try do
                  assert reply == output
                rescue
                  error in [ExUnit.AssertionError] ->
                    reply = cond do
                      is_list(reply) -> Enum.join(reply, "|")
                      true -> reply
                    end
                    raise ExUnit.AssertionError, error.message <> 
                      "\n\t reply: " <> reply <>
                      "\n\t test:  " <> line
                end
            end
          true -> ""
        end
      end)
      |> Stream.run
    end)

  end

end
