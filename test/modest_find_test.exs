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

  test "find selector *" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span>World</span></p>", "span*"})
    assert {:find, "<span>Hello</span>|<span>World</span>"} = reply
  end

  test "find all nodes of type" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span>World</span></p>", "span"})
    assert {:find, "<span>Hello</span>|<span>World</span>"} = reply
  end

  test "find element of type" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<h1>Lorem Ipsum</h1><p>Dolor sit amit</p>", "h1"})
    assert {:find, "<h1>Lorem Ipsum</h1>"} = reply
  end

  test "find selector [name|=\"value\"]" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span name=\"value-name\">World</span></p>", "[name|=\"value\"]"})
    assert {:find, "<span name=\"value-name\">World</span>"} = reply

    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span name=\"value\">World</span></p>", "[name|=\"value\"]"})
    assert {:find, "<span name=\"value\">World</span>"} = reply
  end

  test "find selector [name*=\"value\"]" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span name=\"my-value-name\">World</span></p>", "[name*=\"value\"]"})
    assert {:find, "<span name=\"my-value-name\">World</span>"} = reply

  end

  test "find selector [name~=\"value\"]" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span name=\"my value name\">World</span></p>", "[name~=\"value\"]"})
    assert {:find, "<span name=\"my value name\">World</span>"} = reply

  end

  test "find selector [name$=\"value\"]" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span name=\"my value\">World</span></p>", "[name$=\"value\"]"})
    assert {:find, "<span name=\"my value\">World</span>"} = reply
  end

  test "find selector [name=\"value\"]" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span name=\"value\">World</span></p>", "[name=\"value\"]"})
    assert {:find, "<span name=\"value\">World</span>"} = reply
  end

  # test "find selector [name!=\"value\"]" do
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})

  #   # Select elements that either don’t have the specified attribute, or do have the specified attribute but not with a certain value.

  #   {:error, :timeout} = Cnode.call(pid, {:find, "<p><span id=\"hello\">Hello</span></p><p><span name=\"value\">World</span></p>", "[name!=\"value\"]"})
  #   # assert {:find, "<span id=\"hello\">Hello</span>"} = reply
  # end

  test "find selector [name^=\"value\"]" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span name=\"value name\">World</span></p>", "[name^=\"value\"]"})
    assert {:find, "<span name=\"value name\">World</span>"} = reply
  end

  # test "find selector :button" do
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})

  #   # Selects all button elements and elements of type button.

  #   {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><button>World</button></p>", ":button"})
  #   assert {:find, "<span name=\"value name\">World</span>"} = reply
  # end

  test "find all button" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><button>World</button></p>", "button"})
    assert {:find, "<button>World</button>"} = reply
  end

  # test "find selector :checkbox" do
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})

  #   # Selects all button elements and elements of type button.

  #   {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><input type=\"checkbox\" value=\"World\"></p>", ":checkbox"})
  #   assert {:find, "<button>World</button>"} = reply
  # end

  test "find all input[type=\"checkbox\"]" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><input type=\"checkbox\" value=\"World\"></p>", "input[type=\"checkbox\"]"})
    assert {:find, "<input type=\"checkbox\" value=\"World\"></input>"} = reply
  end

  test "find selector :checked" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><input type=\"checkbox\" value=\"World\" checked></p>", ":checked"})
    assert {:find, "<input type=\"checkbox\" value=\"World\" checked=\"\"></input>"} = reply
  end

  test "find child Selector (parent > child)" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><span>World</span></p>", "p > span"})
    assert {:find, "<span>Hello</span>|<span>World</span>"} = reply
  end

  test "find selector .class" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<h1 class=\"title\">Lorem Ipsum</h1><p>Dolor sit amit</p>", ".title"})
    assert {:find, "<h1 class=\"title\">Lorem Ipsum</h1>"} = reply
  end

  # test "find selector :contains(text)" do
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
  #   {:ok, reply} = Cnode.call(pid, {:find, "<h1>Lorem Ipsum</h1><p>Dolor sit amit</p>", ":contains(\"Lorem Ipsum\")"})
  #   assert {:find, "<h1>Lorem Ipsum</h1>"} = reply
  # end

  test "find ancestor descendant" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<h1><a>some link</a></h1>", "h1 a"})
    assert {:find, "<a>some link</a>"} = reply
  end

  test "find selector :disabled" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><input type=\"checkbox\" value=\"World\" disabled></p>", ":disabled"})
    assert {:find, "<input type=\"checkbox\" value=\"World\" disabled=\"\"></input>"} = reply
  end

  test "find selector :empty" do
    {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
    {:ok, reply} = Cnode.call(pid, {:find, "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>", ":empty"})
    assert {:find, "<head></head>|<p id=\"p1\"></p>|<p id=\"p2\"></p>|<p id=\"p4\"></p>|<p id=\"p5\"></p>|<p id=\"p6\"></p>"} = reply
  end

  # test "find selector :enabled" do
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
  #   {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><input type=\"checkbox\" value=\"World\" disabled=\"disabled\"></p>", "body :enabled"})
  #   assert {:find, "<p><span>Hello</span></p>|<span>Hello</span>"} = reply
  # end

  # test "find selector [enabled=\"true\"]" do
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
  #   {:ok, reply} = Cnode.call(pid, {:find, "<p><span>Hello</span></p><p><input type=\"checkbox\" value=\"World\" disabled=\"disabled\"></p>", "body [enabled=\"true\"]"})
  #   assert {:find, "<p><span>Hello</span></p>|<span>Hello</span>"} = reply
  # end

  # test "find selector :eq(n)" do
  #   {:ok, pid} = Cnode.start_link(%{exec_path: "priv/modest_client"})
  #   {:ok, reply} = Cnode.call(pid, {:find, "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>", ":eq(2)"})
  #   assert {:find, "asdasd"} = reply
  # end

end

