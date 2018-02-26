defmodule GumboQueryClientTest do
  use ExUnit.Case
  alias Nodex.Cnode
  doctest Cnode

  setup_all(_) do
    Nodex.Distributed.up
    # stop slaves that might have not been cleaned up
    Node.list() |> Enum.each(&:slave.stop/1)
    :ok
  end

  test "find link" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/gumbo_query_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<h1><a>some link</a></h1>", "h1 a"})
    assert {:find, "<a>some link</a>"} = reply
  end

  test "find title" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/gumbo_query_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<h1>Lorem Ipsum</h1><p>Dolor sit amit</p>", "h1"})
    assert {:find, "<h1>Lorem Ipsum</h1>"} = reply
  end

  test "find nth-child" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/gumbo_query_client"})
    content = """
    <ul>
      <li>Coffee</li>
      <li>Tea</li>
      <li><span id="milk">Milk</span></li>
    </ul>
    """
    {:ok, reply} = Cnode.call(pid, {:find, content, "li:nth-child(1)"})
    assert {:find, "<li>Coffee</li>"} = reply
  end

  test "find all nodes" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/gumbo_query_client"})
    content = """
    <ul>
      <li>Coffee</li>
      <li>Tea</li>
      <li><span id="milk">Milk</span></li>
    </ul>
    """
    {:ok, reply} = Cnode.call(pid, {:find, content, "li"})
    assert {:find, "<li>Coffee</li><li>Tea</li><li><span id=\"milk\">Milk</span></li>"} = reply
  end

  test "find node with id" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/gumbo_query_client"})
    content = """
    <table>
      <tr>
        <td>First cell in first table. The cell to the right has the second table in it.</td>
        <td>
          <table>
            <tr>
              <td>nested table</td>
            </tr>
            <tr>
              <td id="nested">nested table</td>
            </tr>
          </table>
        </td>
      </tr>
    </table>
    """
    {:ok, reply} = Cnode.call(pid, {:find, content, "td#nested"})
    assert {:find, "<td id=\"nested\">nested table</td>"} = reply
  end

  test "find node with attribute and value" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/gumbo_query_client"})
    content = """
    <ul>
      <li>Coffee</li>
      <li>Tea</li>
      <li><span id="milk">Milk</span></li>
    </ul>
    """
    {:ok, reply} = Cnode.call(pid, {:find, content, "span[id='milk']"})
    assert {:find, "<span id=\"milk\">Milk</span>"} = reply
  end

end

