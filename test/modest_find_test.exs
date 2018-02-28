defmodule ModestFindTest do
  use ExUnit.Case
  alias Nodex.Cnode
  doctest Cnode

  setup_all(_) do
    Nodex.Distributed.up
    :ok
  end

  setup(_) do
    # stop slaves that might have not been cleaned up
    Node.list() |> Enum.each(&:slave.stop/1)
    :ok
  end

  test "can find node with CSS selector" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, {:find, reply}} = Cnode.call(pid, {:find, "<p><a>Hello</a> World</p>", "p a"})
    assert reply == "<a>Hello</a>"
  end

  # test "all selectors from file" do
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})

  #   File.open("test/fixtures/selectors.csv", [:read], fn(file) ->
  #     IO.binstream(file, :line)
  #     |> Stream.map(fn(line) ->
  #       matched = Regex.run(~r/^(0|1);(.*);(.*);(.*)$/, line)
  #       cond do
  #         matched != nil && Enum.count(matched) == 5 && Enum.at(matched, 1) == "1" ->
  #           pattern = Enum.at(matched, 2)
  #           input = Enum.at(matched, 3)
  #           output = Enum.at(matched, 4)
  #           case Cnode.call(pid, {:find, input <> "\0", pattern <> "\0"}) do
  #             {:ok, reply} ->
  #               case reply do
  #                 {:find, result} ->
  #                   try do
  #                     result = assert result == output
  #                   rescue
  #                     error in [ExUnit.AssertionError] ->
  #                       raise ExUnit.AssertionError,
  #                         error.message <>
  #                         "\n\tpattern: " <> pattern <>
  #                         "\n\tinput: " <> input <>
  #                         "\n\tresult: " <> error.left <>
  #                         "\n\texpected: " <> output
  #                   end
  #                 _ -> ""
  #               end
  #             _ ->
  #               raise RuntimeError,
  #                 "\n\tpattern: " <> pattern <>
  #                 "\n\tinput: " <> input <>
  #                 "\n\texpected: " <> output
  #           end
  #         true -> ""
  #       end
  #     end)
  #     |> Stream.run
  #   end)
  # end

end

