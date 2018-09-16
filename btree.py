class BtreeNode(object):
    """
    Class : B Tree Node
    """
    def __init__(self, degree=4):
        """
        initialize B tree node
        :param degree: specify degree of btree  # default degree set to 4
        """
        self.degree = degree
        self.max_data = self.degree-1  # number of keys per node
        self.keys = []  # store keys/data values
        self.children = []  # store child nodes (list of instances of BtreeNode); empty list if node is leaf node

    def __repr__(self):
        return " | ".join(map(str, self.keys))

    @property
    def is_leaf(self):
        return not bool(self.children)

    @property
    def total_keys(self):
        return len(self.keys)

    @property
    def is_balanced(self):
        return self.total_keys <= self.max_data


class Btree(object):
    def __init__(self, degree=4):
        self.degree = degree
        self.root = BtreeNode(degree=degree)

    def search_node(self, start_node, value):
        """

        :param start_node: get root or any non leaf node
        :param value: value to be search
        :return: most matching leaf node
        """
        if start_node.is_leaf:
            return start_node
        else:
            for index in range(len(start_node.keys)-1):  # search for next possible node
                if value < start_node.keys[index]:  # key is greater than value to be search
                    return self.search_node(start_node.children[0], value)
                elif start_node.keys[index] <= value < start_node.keys[index+1]:
                    return self.search_node(start_node.children[index], value)
                else:
                    return self.search_node(start_node.children[index+1], value)

    def search(self, value):
        """
        :param value: value to be search
        :return: leaf node containing value else False
        tuple of 3 values (status, msg, node)
        0 - status of success or failure
        1 - message status
        2 - last explored node
        """
        status, msg, node = None, "", None
        if not self.root.keys:
            # initially no keys/data value - initialize root first
            # msg += "No data in tree..!!"
            status, msg, node = False, "No data in tree..!!", self.root
        else:
            node = self.search_node(self.root, value)
            if node:
                # if current node is leaf then check if value exist in current node or not
                try:
                    node.keys.index(value)
                    status, msg, node = True, "Value found in root node", node
                except ValueError:
                    status, msg, node = False, "Value not found", self.root
        return status, msg, node

    def insert(self, value):
        msg = ""
        if not self.root.keys:
            # initially no keys/data value - initialize root
            self.root.keys.insert(0, value)
            msg += "success"
        else:
            node = self.search(value)
            for index in range(len(node.keys)):
                if node.keys[index] < value:  # if existing value becomes greater than key add it to it's place
                    self.root.keys.insert(index, value)
                    if self.root.is_balanced:
                        msg += "success"
                        break
        return msg


if __name__ == "__main__":
    b = Btree()
    b.insert(5)
