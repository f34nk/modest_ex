defmodule ModestExAttributeTest do
  use ExUnit.Case
  doctest ModestEx

  test "all test cases from file" do
    File.open("test/fixtures/attribute.csv", [:read], fn file ->
      IO.binstream(file, :line)
      |> Stream.map(fn line ->
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
                # output = String.split(Enum.at(matched, 7), "|")
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
                    raise RuntimeError, "\n\tinput: " <> input <> "\n\terror: " <> error

                  # "\n\texpected: " <> Enum.join(output, "|") <>
                  reply ->
                    try do
                      assert reply == output
                    rescue
                      error in [ExUnit.AssertionError] ->
                        raise ExUnit.AssertionError, error.message <> "\n\t test:  " <> line
                        # "\n\t reply: " <> Enum.join(reply, "|") <>
                    end
                end

              "set" ->
                # output = Enum.at(matched, 7)
                test = ModestEx.set_attribute(input, selector, key, value)

                case test do
                  {:error, error} ->
                    raise RuntimeError, "\n\tinput: " <> input <> "\n\terror: " <> error

                  # "\n\texpected: " <> output <>
                  reply ->
                    try do
                      assert reply == output
                    rescue
                      error in [ExUnit.AssertionError] ->
                        raise ExUnit.AssertionError, error.message <> "\n\t test:  " <> line
                        # "\n\t reply: " <> Enum.join(reply, "|") <>
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
