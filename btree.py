class BtreeNode(object):
    def __init__(self, order=4):
        self.order = order
        self.keys = []
        self.children = []
        self.parent = None

    @property
    def is_root(self):
        return not self.parent

    @property
    def is_leaf(self):
        return False if self.children else True

    @property
    def total_keys(self):
        return len(self.children)

    @property
    def is_balanced(self):
        balanced = None
        if self.is_root:
            pass
        else:
            pass
        return balanced

    def insert(self):
        if self.is_balanced:
            pass


if __name__ == "__main__":
    b = BtreeNode()
