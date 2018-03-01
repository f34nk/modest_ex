defmodule ModestExSerializeTest do
  use ExUnit.Case
  doctest ModestEx

  test "all test cases from file" do
  
    File.open("test/fixtures/serialize.csv", [:read], fn(file) ->
      IO.binstream(file, :line)
      |> Stream.map(fn(line) ->
        matched = Regex.run(~r/^(0|1);(.*);(.*)$/, line)
        cond do
          matched != nil && Enum.count(matched) == 4 && Enum.at(matched, 1) == "1" ->
            input = Enum.at(matched, 2)
            output = Enum.at(matched, 3)
            case ModestEx.serialize(input) do
              {:error, _} ->
                raise RuntimeError,
                  "\n\tinput: " <> input <>
                  "\n\texpected: " <> output
              reply ->
                try do
                  assert reply == output
                rescue
                  error in [ExUnit.AssertionError] ->
                    raise ExUnit.AssertionError,
                      error.message <>
                      "\n\tinput: " <> input <>
                      "\n\tresult: " <> error.left <>
                      "\n\texpected: " <> output
                end
            end
          true -> ""
        end
      end)
      |> Stream.run
    end)

  end

end
