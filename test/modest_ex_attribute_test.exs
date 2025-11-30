defmodule ModestExAttributeTest do
  use ExUnit.Case
  doctest ModestEx

  test "all test cases from file" do
    File.open("test/fixtures/attribute.csv", [:read], fn file ->
      file
      |> IO.binstream(:line)
      |> Stream.with_index(1)
      |> Stream.map(fn {line, line_num} ->
        # Enabled;Type;Input;Selector;Key;Value;Output
        matched = Regex.run(~r/^(0|1);(.*);(.*);(.*);(.*);(.*);(.*)$/, line)

        cond do
          matched != nil && Enum.count(matched) == 8 && Enum.at(matched, 1) == "1" ->
            mode = Enum.at(matched, 2)
            input = Enum.at(matched, 3)
            selector = Enum.at(matched, 4)
            key = Enum.at(matched, 5)
            value = Enum.at(matched, 6)
            output = Enum.at(matched, 7)

            case mode do
              "get" ->
                function_name =
                  if selector == "",
                    do: "get_attribute/2",
                    else: "get_attribute/3"

                output =
                  cond do
                    String.contains?(output, "|") -> String.split(output, "|")
                    true -> output
                  end

                test =
                  cond do
                    mode == "get" and selector == "" -> ModestEx.get_attribute(input, key)
                    mode == "get" -> ModestEx.get_attribute(input, selector, key)
                  end

                case test do
                  {:error, error} ->
                    IO.puts("Line #{line_num}: #{function_name} - ERROR: #{inspect(error)}")

                    raise RuntimeError,
                          "\n\tLine: #{line_num}\n\tinput: " <>
                            input <> "\n\terror: " <> inspect(error)

                  reply ->
                    try do
                      assert reply == output
                      IO.puts("Line #{line_num}: #{function_name} #{selector} - SUCCESS")
                    rescue
                      error in [ExUnit.AssertionError] ->
                        IO.puts("Line #{line_num}: #{function_name} #{selector} - FAILURE")

                        raise ExUnit.AssertionError,
                              error.message <>
                                "\n\t Line: #{line_num}\n\t test:  " <>
                                line <> "\n\t selector: " <> selector
                    end
                end

              "set" ->
                function_name = "set_attribute/4"
                test = ModestEx.set_attribute(input, selector, key, value)

                case test do
                  {:error, error} ->
                    IO.puts(
                      "Line #{line_num}: #{function_name} #{selector} - ERROR: #{inspect(error)}"
                    )

                    raise RuntimeError,
                          "\n\tLine: #{line_num}\n\tinput: " <>
                            input <> "\n\terror: " <> inspect(error)

                  reply ->
                    try do
                      assert reply == output
                      IO.puts("Line #{line_num}: #{function_name} #{selector} - SUCCESS")
                    rescue
                      error in [ExUnit.AssertionError] ->
                        IO.puts("Line #{line_num}: #{function_name} #{selector} - FAILURE")

                        raise ExUnit.AssertionError,
                              error.message <> "\n\t Line: #{line_num}\n\t test:  " <> line
                    end
                end
            end

          true ->
            ""
        end
      end)
      |> Stream.run()
    end)
  end
end
