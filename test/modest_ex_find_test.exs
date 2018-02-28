defmodule ModestExFindTest do
  use ExUnit.Case
  doctest ModestEx

  test "all selectors from file" do
  
    File.open("test/fixtures/selectors.csv", [:read], fn(file) ->
      IO.binstream(file, :line)
      |> Stream.map(fn(line) ->
        matched = Regex.run(~r/^(0|1);(.*);(.*);(.*)$/, line)
        cond do
          matched != nil && Enum.count(matched) == 5 && Enum.at(matched, 1) == "1" ->
            pattern = Enum.at(matched, 2)
            input = Enum.at(matched, 3)
            output = Enum.at(matched, 4)
            case ModestEx.find(input, pattern) do
              {:error, _} ->
                raise RuntimeError,
                  "\n\tpattern: " <> pattern <>
                  "\n\tinput: " <> input <>
                  "\n\texpected: " <> output
              {:ok, reply} ->
                try do
                  assert reply == output
                rescue
                  error in [ExUnit.AssertionError] ->
                    raise ExUnit.AssertionError,
                      error.message <>
                      "\n\tpattern: " <> pattern <>
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
