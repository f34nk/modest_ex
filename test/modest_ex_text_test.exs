defmodule ModestExTextTest do
  use ExUnit.Case
  # doctest ModestEx

  test "all test cases from file" do
    File.open("test/fixtures/text.csv", [:read], fn file ->
      file
      |> IO.binstream(:line)
      |> Stream.with_index(1)
      |> Stream.map(fn {line, line_num} ->
        # Enabled;Mode;Input;Selector;Text;Output
        matched = Regex.run(~r/^(0|1);(.*);(.*);(.*);(.*);(.*)$/, line)

        cond do
          matched != nil && Enum.count(matched) == 7 && Enum.at(matched, 1) == "1" ->
            mode = Enum.at(matched, 2)
            input = Enum.at(matched, 3)
            selector = Enum.at(matched, 4)
            text = Enum.at(matched, 5)
            output = Enum.at(matched, 6)

            case mode do
              "get" ->
                function_name =
                  if selector == "",
                    do: "get_text/1",
                    else: "get_text/2"

                output =
                  cond do
                    String.contains?(output, "|") -> String.split(output, "|")
                    true -> output
                  end

                test =
                  cond do
                    mode == "get" and selector == "" -> ModestEx.get_text(input)
                    mode == "get" -> ModestEx.get_text(input, selector)
                  end

                case test do
                  {:error, error} ->
                    IO.puts(
                      "#{function_name} #{selector} (#{line_num}) - ERROR: #{inspect(error)}"
                    )

                    raise RuntimeError,
                          "\n\tLine: #{line_num}\n\tinput: " <>
                            input <> "\n\terror: " <> inspect(error)

                  reply ->
                    try do
                      assert reply == output
                      IO.puts("#{function_name} #{selector} (#{line_num}) - ok")
                    rescue
                      error in [ExUnit.AssertionError] ->
                        IO.puts("#{function_name} #{selector} (#{line_num}) - FAILURE")

                        raise ExUnit.AssertionError,
                              error.message <>
                                "\n\t Line: #{line_num}\n\t test:  " <>
                                line <> "\n\t selector: " <> selector
                    end
                end

              "set" ->
                function_name = "set_text/3"
                test = ModestEx.set_text(input, selector, text)

                case test do
                  {:error, error} ->
                    IO.puts(
                      "#{function_name} #{selector} (#{line_num}) - ERROR: #{inspect(error)}"
                    )

                    raise RuntimeError,
                          "\n\tLine: #{line_num}\n\tinput: " <>
                            input <> "\n\terror: " <> inspect(error)

                  reply ->
                    try do
                      assert reply == output
                      IO.puts("#{function_name} #{selector} (#{line_num}) - ok")
                    rescue
                      error in [ExUnit.AssertionError] ->
                        IO.puts("#{function_name} #{selector} (#{line_num}) - FAILURE")

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
